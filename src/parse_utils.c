/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhpark <junhpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 17:54:58 by junhpark          #+#    #+#             */
/*   Updated: 2021/02/01 16:11:58 by junhpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			get_env_sign(char **cmd)
{
	int			idx;

	if ((*cmd)[0] && (*cmd)[0] == '$')
		(*cmd)[0] = (char)ENV;
	idx = 0;
	while ((*cmd)[++idx])
	{
		if ((*cmd)[idx] == '$' && (*cmd)[idx - 1] != '\\')
			(*cmd)[idx] = (char)ENV;
	}
}

void			remove_quotes(char **cmd)
{
	char		*res;
	int			idx;
	int			res_idx;

	idx = 0;
	res_idx = 0;
	if (ft_strlen(*cmd) == 0)
		return ;
	res = (char *)malloc(sizeof(char) * ft_strlen(*cmd) + 1);
	ft_bzero(res, ft_strlen(*cmd) + 1);
	while ((*cmd)[idx])
	{
		if ((*cmd)[idx] != (char)BIG_Q && (*cmd)[idx] != (char)LIT_Q)
		{
			res[res_idx] = (*cmd)[idx];
			res_idx++;
		}
		idx++;
	}
	res[res_idx] = '\0';
	free(*cmd);
	*cmd = res;
}

void			remove_backslash(char **cmd)
{
	char		*res;
	int			idx;
	int			res_idx;

	idx = 0;
	res_idx = 0;
	if (ft_strlen(*cmd) == 0)
		return ;
	res = (char *)malloc(sizeof(char) * ft_strlen(*cmd) + 1);
	ft_bzero(res, ft_strlen(*cmd) + 1);
	while ((*cmd)[idx])
	{
		if ((*cmd)[idx] == '\\')
			idx++;
		if ((*cmd)[idx])
		{
			res[res_idx] = (*cmd)[idx];
			res_idx++;
			idx++;
		}
	}
	res[res_idx] = '\0';
	free(*cmd);
	*cmd = res;
}

void			delete_subs(char **cmd)
{
	if (cmd != NULL && *cmd != NULL && **cmd != '\0')
	{
		remove_backslash(cmd);
		remove_quotes(cmd);
	}
}

int				is_closed(char *str, int idx)
{
	int			big_q;
	int			lit_q;
	int			start;

	big_q = 0;
	lit_q = 0;
	start = 0;
	while (str[start] && start < idx)
	{
		if (str[start] == (char)BIG_Q)
			big_q++;
		else if (str[start] == (char)LIT_Q)
			lit_q++;
		start++;
	}
	if (lit_q % 2 == 0 && big_q % 2 == 0)
		return (1);
	else
		return (0);
}
