/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyeo <kyeo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 21:23:27 by kyeo              #+#    #+#             */
/*   Updated: 2021/02/02 06:08:35 by kyeo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void
	init_path_data(t_path *path_ptr)
{
	path_ptr->data = ft_split(path_ptr->env->data, ':');
	path_ptr->index = -1;
	path_ptr->command = 0;
	path_ptr->absolute = 0;
}

void
	set_absolute_path(t_path *path_ptr, char **args)
{
	if (is_path(args[0]) == 0)
	{
		path_ptr->command = ft_strjoin("/", args[0]);
		path_ptr->absolute =\
			ft_strjoin(path_ptr->data[path_ptr->index], path_ptr->command);
	}
	else
		path_ptr->absolute = ft_strdup(args[0]);
}

void
	path_join(t_shell *sptr, char **args)
{
	t_path			path;

	if ((path.env = find_env_by_name(sptr->env, "PATH")) == (t_env *)0)
	{
		print_command_error(args[0], 2);
		return ;
	}
	init_path_data(&path);
	while (path.data[++(path.index)])
	{
		set_absolute_path(&path, args);
		if (is_executable_file(path.absolute))
		{
			free_and_change_to_dup(args, 0, path.absolute);
			break ;
		}
		else if (!is_executable_file(path.absolute) &&\
				!(path.data[path.index + 1]))
		{
			print_command_error(args[0], 1);
			break ;
		}
		free_path_data(&path, 0);
	}
	free_path_data(&path, 1);
}
