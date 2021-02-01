/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyeo <kyeo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 15:21:36 by kyeo              #+#    #+#             */
/*   Updated: 2021/02/01 21:31:27 by kyeo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void
	print_command_error(const char *cmd, const int type)
{
	if ((is_executable_file(cmd) == 0))
	{
		write(2, "mini: ", 6);
		write(2, cmd, ft_strlen(cmd));
		write(2, ": ", 2);
		if (type == 1)
			write(2, CMD_NOT_FOUND, CMD_NOT_FOUND_SIZE);
		else
			write(2, NO_FILE_OR_DIR, NO_FILE_OR_DIR_SIZE);
		g_status = 127;
	}
}

void
	execute_binary(t_shell *sptr, char **args)
{
	execve(args[0], args, *(sptr->envp));
}

void
	exec(t_shell *sptr, char **args)
{
	if (is_path(args[0]) && is_executable_file(args[0]))
		execute_binary(sptr, args);
	exit(0);
}
