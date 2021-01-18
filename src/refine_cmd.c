/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refine_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhpark <junhpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 17:48:05 by junhpark          #+#    #+#             */
/*   Updated: 2021/01/18 22:41:50 by junhpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		distinguish_semicolon(char **cmd)
{
	int		idx;

	if ((*cmd)[0] && (*cmd)[0] == ';')
		(*cmd)[0] = (char)DIV;
	idx = 1;
	while ((*cmd)[idx])
	{
		if ((*cmd)[idx] == ';' && (*cmd)[idx - 1] != '\\' && is_closed(*cmd, idx))
			(*cmd)[idx] = (char)DIV;
		idx++;
	}
}

void		revive_quotes(char **cmd)
{
	char	*cmd_dup;
	int		idx;

	cmd_dup = ft_strdup(*cmd);
	idx = 0;
	while ((*cmd)[idx])
	{
		if ((*cmd)[idx] == (char)BIG_Q && !(is_closed(cmd_dup, idx)))
			(*cmd)[idx] = '"';
		else if ((*cmd)[idx] == (char)LIT_Q && !(is_closed(cmd_dup, idx)))
			(*cmd)[idx] = '\'';
		if ((*cmd)[idx] == '"' && (is_closed(cmd_dup, idx + 1)))
			(*cmd)[idx] = (char)BIG_Q;
		else if ((*cmd)[idx] == '\'' && (is_closed(cmd_dup, idx + 1)))
			(*cmd)[idx] = (char)LIT_Q;
		idx++;
	}
	free(cmd_dup);
	cmd_dup = 0;
}

void		distinguish_quotes(char **cmd)
{
	int		idx;

	if ((*cmd)[0] && (*cmd)[0] == '"')
		(*cmd)[0] = (char)BIG_Q;
	else if ((*cmd)[0] && (*cmd)[0] == '\'')
		(*cmd)[0] = (char)LIT_Q;
	idx = 0;
	while ((*cmd)[++idx])
	{
		if ((*cmd)[idx] == '"' && (*cmd)[idx - 1] != '\\')
			(*cmd)[idx] = (char)BIG_Q;
		else if ((*cmd)[idx] == '\'' && (*cmd)[idx - 1] != '\\')
			(*cmd)[idx] = (char)LIT_Q;
	}
	revive_quotes(cmd);
}

void		distinguish_spaces(char **cmd)
{
	int		idx;

	idx = 0;
	while ((*cmd)[idx])
	{
		while ((*cmd)[idx] && is_closed(*cmd, idx))
		{
			if ((*cmd)[idx] == ' ')
				(*cmd)[idx] = (char)SPACE;
			idx++;
		}
		if ((*cmd)[idx])
			idx++;
	}
}

void		refine_cmd(char **cmd)
{
	distinguish_quotes(cmd);
	distinguish_spaces(cmd);
	distinguish_semicolon(cmd);
}
