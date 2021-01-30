/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhpark <junhpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 17:43:48 by junhpark          #+#    #+#             */
/*   Updated: 2021/01/30 16:05:20 by kyeo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		divide_cmds(char ***cmds, char **cmd)
{
	if (*cmd != NULL)
	{
		refine_cmd(cmd);
		(*cmds) = ft_split(*cmd, (char)DIV);
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
