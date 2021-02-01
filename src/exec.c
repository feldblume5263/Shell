/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyeo <kyeo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 15:21:36 by kyeo              #+#    #+#             */
/*   Updated: 2021/02/01 17:36:30 by kyeo             ###   ########.fr       */
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
	execute_binary(t_shell *sptr, char **args)
{
	execve(args[0], args, *(sptr->envp));
}

void
	print_command_error(const char *cmd, const int type)
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

void
	path_join(t_shell *sptr, char **args)
{
	int				path_index;
	char			*command;
	char			*absolute;
	char			**paths;
	t_env			*path_env;

	path_env = find_env_by_name(sptr->env, "PATH");
	if (path_env == (t_env *)0)
	{
		print_command_error(args[0], 2);
		return ;
	}
	paths = ft_split(path_env->data, ':');
	path_index = 0;
	command = 0;
	absolute = 0;
	while (paths[path_index])
	{
		if (!is_path(args[0]))
		{
			command = ft_strjoin("/", args[0]);
			absolute = ft_strjoin(paths[path_index], command);
		}
		else
			absolute = ft_strdup(args[0]);
		if (is_executable_file(absolute))
		{
			free(args[0]);
			args[0] = absolute;
			if (command)
				free(command);
			return ;
		}
		else if (!is_executable_file(absolute) && !(paths[path_index + 1]))
		{
			print_command_error(args[0], 1);
			free(command);
			free(absolute);
			return ;
		}
		free(command);
		free(absolute);
		path_index += 1;
	}
}

void
	exec(t_shell *sptr, char **args)
{
	if (is_path(args[0]) && is_executable_file(args[0]))
		execute_binary(sptr, args);
	exit(0);
}
