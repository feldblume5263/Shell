/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhpark <junhpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 16:09:44 by junhpark          #+#    #+#             */
/*   Updated: 2021/01/25 16:14:56 by kyeo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int				find_redir(char *chunk)
{
	if (chunk && ft_strlen(chunk) == 1 && ft_strncmp(chunk, "<", 1) == 0)
		return (1);
	else if (chunk && ft_strlen(chunk) == 1 && ft_strncmp(chunk, ">", 1) == 0)
		return (2);
	else if (chunk && ft_strlen(chunk) == 2 && ft_strncmp(chunk, ">>", 2) == 0)
		return (3);
	else
		return (0);
}

void			get_redir(char *red, char ***res)
{
	int			res_i;

	res_i = 0;
	if (!(*red))
		return ;
	while (*res && (*res)[res_i])
		res_i++;
	(*res)[res_i] = ft_strdup(red);
	(*res)[++res_i] = 0;
}

void			ch_without_redir(char ***data, char ***res, char ***redir)
{
	int			cmd_i;
	int			res_i;

	cmd_i = -1;
	res_i = 0;
	while ((*data)[++cmd_i])
	{
		if (cmd_i == 0 && find_redir((*data)[cmd_i]) == 0)
			(*res)[res_i++] = ft_strdup((*data)[cmd_i]);
		else if (cmd_i > 0 && find_redir((*data)[cmd_i]) == 0
			&& find_redir((*data)[cmd_i - 1]) == 0)
			(*res)[res_i++] = ft_strdup((*data)[cmd_i]);
		else
			get_redir((*data)[cmd_i], redir);
	}
	(*res)[res_i] = 0;
	cmd_i = -1;
	while ((*data)[++cmd_i])
	{
		free((*data)[cmd_i]);
		(*data)[cmd_i] = 0;
	}
	free(*data);
	*data = *res;
}

int				parse_redirection(char ***data, char ***redir)
{
	char		**res;

	if (count_all(*data) == 0)
		return (0);
	res = (char **)malloc(sizeof(char *) * (count_ch(*data) + 1));
	*redir = (char **)malloc(sizeof(char *) * (count_all(*data) - count_ch(*data) + 1));
	init_redir(redir, count_all(*data) - count_ch(*data) + 1);
	ch_without_redir(data, &res, redir);
	return (1);
}
