/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhpark <junhpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 22:31:32 by junhpark          #+#    #+#             */
/*   Updated: 2021/01/18 04:37:17 by junhpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../include/libft.h"
# include <limits.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
#include <stdio.h>

#define BIG_Q 128
#define LIT_Q 129
#define SPACE 130
#define DIV 131

void		remove_quotes(char **cmd)
{
	char	*res;
	int		idx;
	int		res_idx;

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

void		remove_backslash(char **cmd)
{
	char	*res;
	int		idx;
	int		res_idx;

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
		res[res_idx] = (*cmd)[idx];
		res_idx++;
		idx++;
	}
	res[res_idx] = '\0';
	free(*cmd);
	*cmd = res;
}

void			parse_command(char *raw) // \n 이 없음 (\n을 따로 빼지 않아도 괜찮음.)
{
	char		**data;

	data = ft_split(raw, (char)SPACE);
	remove_quotes(&(data[0]));
	if (ft_strlen(data[0]) == 4 && ft_strncmp(data[0], "echo", 4) == 0)
	{
		write(1, "run echo\n", 9);
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

int			cmd_join(char **cmd, char *buf, int size)
{
	int		i;
	int		j;
	char	*new;

	if (!(new = malloc(sizeof(char) * (size + 1))))
		return (-1);
	i = 0;
	while (*cmd != (char *)0 && (*cmd)[i])
	{
		new[i] = (*cmd)[i];
		i++;
	}
	j = 0;
	while (buf[j])
	{
		new[i + j] = buf[j];
		j++;
	}
	new[i + j] = '\0';
	if (*cmd != (char *)0)
		free(*cmd);
	*cmd = new;
	return (1);
}

int			make_cmd(char buf[], char **cmd)
{
	int		size;

	if (*cmd == (char *)0)
		size = ft_strlen(buf);
	else
		size = ft_strlen(*cmd) + ft_strlen(buf);
	cmd_join(cmd, buf, size);
	return (size);
}

void		getcmd(char **cmd)
{
	int		ret;
	char	buf[4096 + 1];
	int		idx;
	int		nl;

	nl = 0;
	ft_bzero(buf, 4097);
	while ((ret = read(0, buf, 4096)) > 0)
	{
		buf[ret] = '\0';
		idx = -1;
		while (buf[++idx])
		{
			if (buf[idx] == '\n')
				nl = 1;
		}
		make_cmd(buf, cmd);
		ft_bzero(buf, 4097);
		if (nl == 1)
			break ;
	}
}

void		print_prompt(void)
{
	write(1, "minishell # ", 12);
}

void		distinguish_semicolon(char **cmd)
{
	int		idx;

	if ((*cmd)[0] && (*cmd)[0] == ';')
		(*cmd)[0] = (char)DIV;
	idx = 1;
	while ((*cmd)[idx])
	{
		if ((*cmd)[idx] == ';' && (*cmd)[idx - 1] != '\\')
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
	// remove_backslash(cmd);
	// remove_quotes(cmd);
}

void		divide_cmds(char ***cmds, char **cmd)
{
	refine_cmd(cmd);
	(*cmds) = ft_split(*cmd, (char)DIV);
}


void		prompt()
{
	char	**cmds;
	char	*cmd;
	int		cmd_idx;

	cmd = 0;
	while (1)
	{
		print_prompt();
		getcmd(&cmd);
		divide_cmds(&cmds, &cmd);
		cmd_idx = -1;
		while (cmds[++cmd_idx])
		{
			if (!(cmds[cmd_idx + 1]))
				cmds[cmd_idx][ft_strlen(cmds[cmd_idx]) - 1] = '\0';
			write(1, cmds[cmd_idx], ft_strlen(cmds[cmd_idx])); // test
			write(1, "\n", 1); // test
			parse_command(cmds[cmd_idx]);
			free(cmds[cmd_idx]);
			cmds[cmd_idx] = 0;
		}
		free(cmd);
		cmd = 0;
	}
}

int				main(void)
{
	prompt();
	return (0);
}
