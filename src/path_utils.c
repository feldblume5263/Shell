/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyeo <kyeo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 06:08:08 by kyeo              #+#    #+#             */
/*   Updated: 2021/02/02 06:08:32 by kyeo             ###   ########.fr       */
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
	free_and_change_to_dup(char **args, const int arg_index, const char *new)
{
	free_ptr(&(args[arg_index]));
	args[arg_index] = ft_strdup(new);
}
