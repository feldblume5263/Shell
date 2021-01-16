/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyeo <kyeo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 15:21:36 by kyeo              #+#    #+#             */
/*   Updated: 2021/01/16 21:02:31 by kyeo             ###   ########.fr       */
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

int
	is_executable_file(const char *command)
{
	struct stat		buf;

	stat(command, &buf);
	if (S_ISREG(buf.st_mode) && (S_IXUSR & buf.st_mode))
		return (1);
	return (0);
}

void
	execute_binary(char **args)
{
	pid_t			pid;

	pid = fork();
	if (pid == 0)
		execve(args[0], args, NULL);
	else
		waitpid(pid, 0, 0);
}

void
	path_join(t_shell *sptr, char **args)
{
	int				path_index;
	char			*command;
	char			*absolute;
	char			**paths;
	t_env			*path_env;

	path_env = find_env_by_name(sptr->env, "PATH");
	paths = ft_split(path_env->data, ':');
	path_index = 0;
	while (paths[path_index])
	{
		command = ft_strjoin("/", args[0]);
		absolute = ft_strjoin(paths[path_index], command);
		if (is_executable_file(absolute))
		{
			free(args[0]);
			args[0] = absolute;
			execute_binary(args);
			free(command);
			return ;
		}
		else
		{
			// error handling
		}
		free(command);
		free(absolute);
		path_index += 1;
	}
}

void
	exec(t_shell *sptr, char **args)
{
	(void)sptr;
	if (is_path(args[0]) && is_executable_file(args[0]))
		execute_binary(args);
	else
		path_join(sptr, args);
}
