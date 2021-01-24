/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhpark <junhpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/24 11:12:19 by junhpark          #+#    #+#             */
/*   Updated: 2021/01/24 11:13:03 by junhpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int				count_ch(char **data)
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

int				count_all(char **data)
{
	int			idx;

	idx = 0;
	while (data[idx])
		idx++;
	return (idx);
}

void			init_redir(char ***redir, int size)
{
	int			idx;

	idx = 0;
	while (idx < size)
	{
		(*redir)[idx] = 0;
		idx++;
	}
}
