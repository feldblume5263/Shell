/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhpark <junhpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 19:22:50 by junhpark          #+#    #+#             */
/*   Updated: 2021/02/01 15:24:46 by kyeo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int
	count_add_space(char *cmd)
{
	int		idx[2];

	idx[0] = -1;
	idx[1] = 0;
	while (cmd[++idx[0]])
	{
		if (is_closed(cmd, idx[0]) && cmd[idx[0]] == '>'\
			&& cmd[idx[0] + 1] && cmd[idx[0] + 1] == '>')
		{
			if (idx[0] > 0 && cmd[idx[0] - 1] != (char)SPACE)
				idx[1]++;
			if (cmd[idx[0] + 2] && cmd[idx[0] + 2] != (char)SPACE)
				idx[1]++;
			idx[0]++;
		}
		else if (is_closed(cmd, idx[0]) && (cmd[idx[0]] == '>' ||\
			cmd[idx[0]] == '<' || cmd[idx[0]] == '|'))
		{
			if (idx[0] > 0 && cmd[idx[0] - 1] != (char)SPACE)
				idx[1]++;
			if (cmd[idx[0] + 1] && cmd[idx[0] + 1] != (char)SPACE)
				idx[1]++;
		}
	}
	return (idx[1]);
}

void
	put_others(char *cmd, char **res, int *idx, int *res_idx)
{
	if ((*idx) > 0 && cmd[(*idx) - 1] != (char)SPACE)
		(*res)[++(*res_idx)] = (char)SPACE;
	(*res)[++(*res_idx)] = cmd[(*idx)];
	if (cmd[(*idx) + 1] && cmd[(*idx) + 1] != (char)SPACE)
		(*res)[++(*res_idx)] = (char)SPACE;
}

void
	put_redirdouble(char *cmd, char **res, int *idx, int *res_idx)
{
	if ((*idx) > 0 && cmd[(*idx) - 1] != (char)SPACE)
		(*res)[++(*res_idx)] = (char)SPACE;
	(*res)[++(*res_idx)] = cmd[(*idx)];
	(*res)[++(*res_idx)] = cmd[(*idx) + 1];
	if (cmd[(*idx) + 2] && cmd[(*idx) + 2] != (char)SPACE)
		(*res)[++(*res_idx)] = (char)SPACE;
	if (cmd[(*idx) + 1])
		(*idx)++;
}

void
	reload_line(char *cmd, char **res)
{
	int		idx;
	int		res_idx;

	idx = -1;
	res_idx = -1;
	while (cmd[++idx])
	{
		if (is_closed(cmd, idx) && cmd[idx] == '>'\
			&& cmd[idx + 1] && cmd[idx + 1] == '>')
			put_redirdouble(cmd, res, &idx, &res_idx);
		else if (is_closed(cmd, idx) && (cmd[idx] == '>' ||\
			cmd[idx] == '<' || cmd[idx] == '|'))
			put_others(cmd, res, &idx, &res_idx);
		else if (cmd[idx] != '\n')
			(*res)[++res_idx] = cmd[idx];
	}
	(*res)[++res_idx] = '\0';
}

void
	insert_appro_space(char **cmd)
{
	char	*res;
	int		size;

	if (*cmd == NULL || ft_strlen(*cmd) == 0)
		return ;
	size = ft_strlen(*cmd) + count_add_space(*cmd);
	if (!(res = (char *)malloc(sizeof(char) * (size + 1))))
		return ;
	reload_line(*cmd, &res);
	free(*cmd);
	*cmd = res;
}
