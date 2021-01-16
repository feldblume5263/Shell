/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhpark <junhpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 13:38:48 by junhpark          #+#    #+#             */
/*   Updated: 2021/01/16 18:35:21 by junhpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef struct	s_ch
{
	int			count;
	int			size;
	int			big_q;
	int			lit_q;
}				t_ch;

void			put_string(char **res, char *cmd)
{
	int		cmd_idx;
	int		res_idx;

	cmd_idx = 0;
	res_idx = 0;
	while (cmd[cmd_idx])
	{
		if (cmd[cmd_idx] == '"')
		{
			cmd_idx++;
			while (cmd[cmd_idx] && cmd[cmd_idx] != '"')
				(*res)[res_idx++] = cmd[cmd_idx++];
		}
		else if (cmd[cmd_idx] == '\'')
		{
			cmd_idx++;
			while (cmd[cmd_idx] && cmd[cmd_idx] != '\'')
				(*res)[res_idx++] = cmd[cmd_idx++];
		}
		else
			(*res)[res_idx++] = cmd[cmd_idx];
		cmd_idx++;
	}
	(*res)[res_idx] = '\0';
}

char			*rewrite_chunk(char *cmd, t_ch *chunk)
{
	char	*res;

	res = (char *)malloc(sizeof(char) * chunk->size + 1);
	put_string(&res, cmd);
	return (res);
}

void			get_chunk(char *cmd, t_ch *chunk)
{
	int		idx;

	idx = -1;
	while (cmd[++idx])
	{
		if (cmd[idx] && cmd[idx] == '"' && chunk->count++ != -1)
		{
			idx++;
			while (cmd[idx] != '"' && cmd[idx])
				idx++;
			if (!cmd[idx] && chunk->count-- != -1)
				chunk->big_q = 0;
		}
		else if (cmd[idx] && cmd[idx] == '\'' && chunk->count++ != -1)
		{
			idx++;
			while (cmd[idx] != '\'' && cmd[idx])
				idx++;
			if (!cmd[idx] && chunk->count-- != -1)
				chunk->lit_q = 0;
		}
		if (cmd[idx] == '\0')
			break ;
	}
}

void			init_chunk(t_ch *chunk)
{
	chunk->count = 0;
	chunk->big_q = 1;
	chunk->lit_q = 1;
}

void			handle_quotes(char **cmd)
{
	char	*res;
	t_ch	chunk;
	char	*add_buf;
	char	*temp;

	chunk.big_q = 0;
	chunk.lit_q = 0;
	add_buf = 0;
	while (chunk.big_q == 0 || chunk.lit_q == 0)
	{
		init_chunk(&chunk);
		get_chunk(*cmd, &chunk);
		chunk.size = ft_strlen(*cmd) - (chunk.count * 2);
		if (chunk.big_q == 0 || chunk.lit_q == 0)
		{
			write(1, "> ", 2);
			getcmd(&add_buf);
			temp = ft_strjoin(*cmd, add_buf);
			safe_free(*cmd);
			safe_free_temp(&add_buf);
			*cmd = temp;
		}
	}
	res = rewrite_chunk(*cmd, &chunk);
	safe_free(*cmd);
	*cmd = res;
}
