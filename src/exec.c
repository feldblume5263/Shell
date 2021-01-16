/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyeo <kyeo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 15:21:36 by kyeo              #+#    #+#             */
/*   Updated: 2021/01/16 16:38:32 by kyeo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int
	is_path(const char *command)
{
	if (ft_strncmp(command, "./", 2) == 0 ||\
		ft_strncmp(command, "../", 3) == 0 ||\
		ft_strncmp(command, "/", 1) == 0)
		return (1);
	return (0);
}

void
	execute_binary(char **args)
{
	pid_t			pid;

	pid = fork();
	printf("ARG0: %s\n", args[0]);
	if (pid == 0)
		execve(args[0], args, NULL);
	else
		waitpid(pid, 0, 0);
}

void
	exec(t_shell *sptr, char **args)
{
	struct stat		buf;

	(void)sptr;
	printf("ARG0: %s\n", args[0]);
	printf("STAT: %d\n", stat(args[0], &buf));
	printf("FILE: %d\n", S_ISREG(buf.st_mode));
	printf("EXEC: %d\n", S_IXUSR & buf.st_mode);
	execute_binary(args);
}
