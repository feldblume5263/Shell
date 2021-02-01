/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhpark <junhpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/24 11:12:19 by junhpark          #+#    #+#             */
/*   Updated: 2021/02/01 21:50:21 by kyeo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void
	remake_redir(char **cmds)
{
	int			cmd_idx;
	int			idx;

	cmd_idx = -1;
	while (cmds[++cmd_idx])
	{
		idx = -1;
		while (cmds[cmd_idx][++idx])
		{
			if (cmds[cmd_idx][idx] == (char)RDROUT)
				cmds[cmd_idx][idx] = '>';
			else if (cmds[cmd_idx][idx] == (char)RDRIN)
				cmds[cmd_idx][idx] = '<';
		}
	}
}

int
	count_ch(char **data)
{
	int			cmd_i;
	int			count;

	cmd_i = 0;
	count = 0;
	while (data[cmd_i])
	{
		if (cmd_i == 0 && find_redir(data[cmd_i]) == 0)
			count++;
		else if (cmd_i > 0 && !find_redir(data[cmd_i])
			&& !find_redir(data[cmd_i - 1]))
			count++;
		cmd_i++;
	}
	return (count);
}

int
	count_all(char **data)
{
	int			idx;

	idx = 0;
	while (data[idx])
		idx++;
	return (idx);
}

void
	init_redir(char ***redir, int size)
{
	int			idx;

	idx = 0;
	while (idx < size)
	{
		(*redir)[idx] = 0;
		idx++;
	}
}
