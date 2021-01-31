/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhpark <junhpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 17:43:48 by junhpark          #+#    #+#             */
/*   Updated: 2021/01/31 17:05:36 by junhpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		finish_cycle(char ***cmds, char **cmd, t_shell *sptr)
{
	(void)sptr;
	free_ptr(cmd);
	free_double_ptr((void ***)cmds);
	restore_std(sptr);
}

void		divide_cmds(char ***cmds, char **cmd)
{
	if (*cmd != NULL)
	{
		refine_cmd(cmd);
		insert_appro_space(cmd);
		(*cmds) = ft_split(*cmd, (char)DIV);
	}
	else
		*cmds = NULL;
}

void		print_prompt()
{
	write(1, "minishell # ", 12);
}

void		sig_handler(int signo)
{
	if (signo == SIGINT)
	{
		g_status = 1;
		write(1, "\n", 1);
		print_prompt();
	}
}

void		run_error()
{

}

void		restore_std(t_shell *sptr)
{
	dup2(sptr->saved_stdout, STDOUT_FILENO);
	dup2(sptr->saved_stdin, STDIN_FILENO);
}

void		prepare_std(t_shell *sptr)
{
	sptr->saved_stdout = dup(STDOUT_FILENO);
	sptr->saved_stdin = dup(STDIN_FILENO);
	sptr->exit_code = 1;
	g_status = 0;
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, SIG_IGN);
}

void		prompt(t_shell *sptr)
{
	char	**cmds;
	char	*cmd;
	int		cmd_idx;

	cmd = 0;
	prepare_std(sptr);
	while (sptr->exit_code)
	{
		print_prompt();
		getcmd(&cmd);
		if (cmd == NULL)
			break ;
		divide_cmds(&cmds, &cmd);
		if (handle_cmd_error(cmds, cmd) < 0)
		{
			finish_cycle(&cmds, &cmd, sptr);
			continue ;
		}
		cmd_idx = -1;
		while (cmds && cmds[++cmd_idx])
			if (cmds[cmd_idx] != NULL)
				parse_command(sptr, cmds[cmd_idx]);
		finish_cycle(&cmds, &cmd, sptr);
		g_status = 0;
	}
}
