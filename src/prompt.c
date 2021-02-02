/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhpark <junhpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 17:43:48 by junhpark          #+#    #+#             */
/*   Updated: 2021/02/02 12:58:55 by junhpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void
	divide_cmds(char ***cmds, char **cmd)
{
	if (*cmd != NULL)
	{
		change_redir(cmd);
		refine_cmd(cmd);
		get_env_sign(cmd);
		insert_appro_space(cmd);
		(*cmds) = ft_split(*cmd, (char)DIV);
	}
	else
		*cmds = NULL;
}

void
	print_prompt(void)
{
	write(1, "minishell # ", 12);
}

void
	sig_handler(int signo)
{
	if (signo == SIGINT)
	{
		g_status = 1;
		write(1, "\n", 1);
		print_prompt();
	}
}

void
	prepare_std(t_shell *sptr)
{
	sptr->saved_stdout = dup(STDOUT_FILENO);
	sptr->saved_stdin = dup(STDIN_FILENO);
	sptr->exit_code = 1;
	g_status = 0;
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, SIG_IGN);
}

void
	launch_cmd(char **cmds, t_shell *sptr)
{
	int		cmd_idx;

	cmd_idx = -1;
	while (cmds && cmds[++cmd_idx])
	{
		if (cmds[cmd_idx] != NULL)
			parse_command(sptr, cmds[cmd_idx]);
	}
}

void
	prompt(t_shell *sptr)
{
	char	**cmds;
	char	*cmd;
	char	*temp;

	cmd = 0;
	cmds = 0;
	prepare_std(sptr);
	while (sptr->exit_code)
	{
		print_prompt();
		getcmd(&cmd);
		if (cmd == NULL)
			break ;
		divide_cmds(&cmds, &cmd);
		temp = ft_strdup(cmd);
		if (handle_cmd_error(temp) < 0)
		{
			finish_cycle(&cmds, &cmd, sptr);
			continue ;
		}
		launch_cmd(cmds, sptr);
		free_ptr(&temp);
		finish_cycle(&cmds, &cmd, sptr);
	}
}
