/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhpark <junhpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 17:43:48 by junhpark          #+#    #+#             */
/*   Updated: 2021/01/28 15:47:34 by junhpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			find_system_dup(char **data) // *수정
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
		idx++;
	}
	return (1);
}

int			find_system_error(char **cmds) // *수정
{
	int		cmd_idx;
	char	**data;

	if (cmds == 0)
		return (0);
	cmd_idx = 0;
	while (cmds[cmd_idx])
	{
		data  = ft_split(cmds[cmd_idx], (char)SPACE);
		if (find_system_dup(data) < 0)
			return (-1);
		free_double(&data);
		cmd_idx++;
	}
	return (1);
}

int			count_add_space(char *cmd)
{
	int		idx;
	int		count;

	idx = -1;
	count = 0;
	while (cmd[++idx])
	{
		if (cmd[idx] == '>')
		{
			if (idx > 0 && cmd[idx - 1] != (char)SPACE\
				&& cmd[idx - 1] != '<' && cmd[idx - 1] != '>')
				count++;
			if (cmd[idx + 1] && cmd[idx - 1] != (char)SPACE\
				&& cmd[idx + 1] != '<' && cmd[idx + 1] != '>')
				count++;)
		}
	}
}

void		insert_appro_space(char **cmd)
{
	char	*res;

	if (*cmd == NULL || ft_strlen(*cmd) == 0)
		return ;
	if (!(res = (char *)malloc(sizeof(char) *\
		(ft_strlen(*cmd) + count_add_space(*cmd) + 1))))
		return ;
}

int			divide_cmds(char ***cmds, char **cmd)
{
	refine_cmd(cmd);
	insert_appro_space(cmd);
	(*cmds) = ft_split(*cmd, (char)DIV);
	if (find_system_error(*cmds) < 0) // *수정
	{
		write(1, "bash: syntax error near unexpected token\n", 41);
		return (-1);
	}
	return (1);
}

void		print_prompt()
{
	write(1, "minishell # ", 12);
}

void		prompt(t_shell *sptr)
{
	char	**cmds;
	char	*cmd;
	int		cmd_idx;

	cmd = 0;
	while (1)
	{
		print_prompt();
		getcmd(&cmd);
		if (divide_cmds(&cmds, &cmd) < 0) // *수정
			break ; // *수정
		cmd_idx = -1;
		while (cmds[++cmd_idx])
		{
			if (!(cmds[cmd_idx + 1]))
				cmds[cmd_idx][ft_strlen(cmds[cmd_idx]) - 1] = '\0';
			parse_command(sptr, cmds[cmd_idx]);
			free(cmds[cmd_idx]);
			cmds[cmd_idx] = 0;
		}
		free(cmd);
		cmd = 0;
		free(cmds);
		cmds = 0;
	}
}
