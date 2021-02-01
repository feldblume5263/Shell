/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_end.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhpark <junhpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/31 19:23:59 by junhpark          #+#    #+#             */
/*   Updated: 2021/02/01 15:23:44 by kyeo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void
	finish_cycle(char ***cmds, char **cmd, t_shell *sptr)
{
	(void)sptr;
	free_ptr(cmd);
	free_double_ptr((void ***)cmds);
	restore_std(sptr);
}

void
	restore_std(t_shell *sptr)
{
	dup2(sptr->saved_stdout, STDOUT_FILENO);
	dup2(sptr->saved_stdin, STDIN_FILENO);
}
