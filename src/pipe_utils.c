/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyeo <kyeo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/31 16:55:56 by kyeo              #+#    #+#             */
/*   Updated: 2021/02/02 13:50:24 by kyeo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void
	swap_fd_value(int *old, int *new)
{
	old[0] = new[0];
	old[1] = new[1];
}

void
	wait_loop(const int max)
{
	int			count;
	int			status;

	count = 0;
	while (count < max)
	{
		wait(&status);
		if (status == 256)
			g_status = 2;
		else
			g_status = 0;
		count += 1;
	}
}

void
	pipe_child(t_cmd *cptr)
{
	if (cptr->cmds_index)
		dup2_and_close(cptr->pip.old_fds, 0);
	if (cptr->cmds_redirected[cptr->cmds_index + 1])
		dup2_and_close(cptr->pip.new_fds, 1);
}

void
	pipe_parent(t_shell *sptr, t_cmd *cptr)
{
	if (cptr->cmds_index)
		dup2_and_close(cptr->pip.old_fds, -1);
	if (cptr->cmds_redirected[cptr->cmds_index + 1])
		swap_fd_value(cptr->pip.old_fds, cptr->pip.new_fds);
	if (cptr->builtins == 1)
		dispence_command(sptr, cptr->cmds_redirected[cptr->cmds_index],\
				cptr->builtins);
}

void
	pipe_end(t_cmd *cptr, t_pipe *pptr, const int cmds_index)
{
	if (cmds_index)
		dup2_and_close(pptr->old_fds, -1);
	wait_loop(pptr->num_pipes + 1);
	dup2_and_close(pptr->old_fds, -1);
	dup2_and_close(pptr->new_fds, -1);
	if (cptr->cmds_redirected[cmds_index] == 0)
	{
		free_double_ptr((void ***)cptr->cmds_redirected);
		free(cptr->cmds_redirected);
		cptr->cmds_redirected = 0;
	}
}
