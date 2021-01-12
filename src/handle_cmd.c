/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhpark <junhpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 13:38:48 by junhpark          #+#    #+#             */
/*   Updated: 2021/01/12 18:11:15 by junhpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

typedef struct	s_ch
{
	int			count;
	int			size;
	int			big_q;
	int			lit_q;
}				t_ch;

char	*join_newline(char const *s1, char const *s2)
{
	char	*newstr;
	int		i;
	int		j;

	if (!(s1) || !(s2))
		return (0);
	i = -1;
	j = 0;
	newstr = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 2));
	if (!(newstr))
		return (0);
	while (s1[++i])
		newstr[i] = s1[i];
	// if (newstr[i] != '\n')
	// 	newstr[i++] = '\n';
	while (s2[j])
	{
		newstr[i] = s2[j];
		j++;
		i++;
	}
	newstr[i] = '\0';
	return (newstr);
}

void		safe_free(void *p)
{
	if (p && (char *)p)
	{
		free(p);
		p = 0;
	}
}

void		put_string(char **res, char *cmd)
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
}

char		*rewrite_chunk(char *cmd, t_ch *chunk)
{
	char	*res;
	char	add[100];

	res = (char *)malloc(sizeof(char) * chunk->size + 1);
	put_string(&res, cmd);
	return (res);
}

void		get_chunk(char *cmd, t_ch *chunk)
{
	int		idx;

	idx = -1;
	chunk->big_q = 1;
	chunk->lit_q = 1;
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
	}
}

void		handle_quotes(char **cmd)
{
	char	*res;
	t_ch	chunk;
	char	add_buf[100];
	char	*temp;

	chunk.big_q = 0;
	chunk.lit_q = 0;
	// 얘를 함수 한줄로 만들어서 -> buffer 무한으로 받기
	while (chunk.big_q == 0 || chunk.lit_q == 0)
	{
		ft_bzero(add_buf, 100);
		chunk.count = 0;
		get_chunk(*cmd, &chunk);
		chunk.size = ft_strlen(*cmd) - (chunk.count * 2);
		if (chunk.big_q == 0 || chunk.lit_q == 0)
		{
			write(1, "> ", 2);
			read(0, add_buf, 100);
			temp = ft_strjoin(*cmd, add_buf);
			safe_free(*cmd);
			*cmd = temp;
		}
	}
	res = rewrite_chunk(*cmd, &chunk);
	safe_free(*cmd);
	*cmd = res;
}

// int			main(void)
// {
// 	char	*buf;

// 	while (1)
// 	{
// 		buf = (char *)malloc(sizeof(char) * 100);
// 		ft_bzero(buf, 100);
// 		read(0, buf, 100);
// 		handle_quotes(&buf);
// 		printf("%s", buf);
// 		free(buf);
// 	}
// 	// while (1) {}
// 	return (0);
// }
