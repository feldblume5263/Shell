/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhpark <junhpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 19:30:05 by junhpark          #+#    #+#             */
/*   Updated: 2021/02/01 17:51:43 by kyeo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int
	find_system_dup(char **data)
{
	int		idx;

	idx = 0;
	while (data[idx])
	{
		if (idx > 0 && find_redir(data[idx]) > 0)
		{
			if (find_redir(data[idx - 1]) > 0)
				return (-1);
		}
		if (!data[idx + 1])
		{
			if (find_redir(data[idx]) > 0)
				return (-1);
		}
		idx++;
	}
	return (1);
}

int
	find_system_error(char **cmds)
{
	int		cmd_idx;
	char	**data;

	if (cmds == 0)
		return (0);
	cmd_idx = -1;
	while (cmds[++cmd_idx])
	{
		data = ft_split(cmds[cmd_idx], (char)SPACE);
		if (find_system_dup(data) < 0)
			return (-1);
		free_double_ptr((void ***)&data);
	}
	return (1);
}

int
	handle_cmd_error(char **cmds, char *cmd)
{
	(void)cmd;
	if (find_system_error(cmds) < 0)
	{
		write(2, "mini: syntax error near unexpected token\n", 41);
		g_status = 2;
		return (-1);
	}
	return (1);
}
