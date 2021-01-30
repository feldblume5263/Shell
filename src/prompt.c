/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhpark <junhpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 17:43:48 by junhpark          #+#    #+#             */
/*   Updated: 2021/01/30 16:27:30 by kyeo             ###   ########.fr       */
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
		free_double_ptr((void ***)&data);
		cmd_idx++;
	}
	return (1);
}

int			count_add_space(char *cmd)
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

void		put_others(char *cmd, char **res, int *idx, int *res_idx)
{
	if ((*idx) > 0 && cmd[(*idx) - 1] != (char)SPACE)
		(*res)[++(*res_idx)] = (char)SPACE;
	(*res)[++(*res_idx)] = cmd[(*idx)];
	if (cmd[(*idx) + 1] && cmd[(*idx) + 1] != (char)SPACE)
		(*res)[++(*res_idx)] = (char)SPACE;
}

void		put_redirdouble(char *cmd, char **res, int *idx, int *res_idx)
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

void		reload_line(char *cmd, char **res)
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
		else
			(*res)[++res_idx] = cmd[idx];
	}
	(*res)[++res_idx] = '\0';
}

void		insert_appro_space(char **cmd)
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

void		divide_cmds(char ***cmds, char **cmd)
{
	if (*cmd != NULL)
	{
		refine_cmd(cmd);
		insert_appro_space(cmd);
		(*cmds) = ft_split(*cmd, (char)DIV);
		if (find_system_error(*cmds) < 0)  // 나중에 함께 에러 처리
			write(2, "bash: syntax error near unexpected token\n", 41);
	}
	else
		*cmds = NULL;
}

void		print_prompt()
{
	write(1, "minishell # ", 12);
}

void
	sig_handler(int signo)
{
	if (signo == SIGINT)
	{
		write(1, "\n", 1);
		print_prompt();
	}
}

void		prompt(t_shell *sptr)
{
	char	**cmds;
	char	*cmd;
	int		cmd_idx;
	int		saved_stdout;
	int		saved_stdin;

	saved_stdout = dup(STDOUT_FILENO);
	saved_stdin = dup(STDIN_FILENO);
	cmd = 0;
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, SIG_IGN);
	while (g_status)
	{
		print_prompt();
		getcmd(&cmd);
		if (cmd == NULL)
			break ;
		divide_cmds(&cmds, &cmd);
		cmd_idx = -1;
		while (cmds && cmds[++cmd_idx])
		{
			if (!(cmds[cmd_idx + 1]))
				cmds[cmd_idx][ft_strlen(cmds[cmd_idx]) - 1] = '\0';
			if (cmds[cmd_idx] != NULL)
				parse_command(sptr, cmds[cmd_idx]);
		}
		free(cmd);
		cmd = 0;
		free_double_ptr((void ***)&cmds);
		dup2(saved_stdout, STDOUT_FILENO);
		dup2(saved_stdin, STDIN_FILENO);
	}
}
