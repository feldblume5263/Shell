/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyeo <kyeo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 20:19:39 by kyeo              #+#    #+#             */
/*   Updated: 2021/02/02 20:24:56 by kyeo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void
	print_prompt(void)
{
	write(2, "minishell # ", 13);
}

void
	prepare_std(t_shell *sptr, char **cmd, char ***cmds)
{
	sptr->saved_stdout = dup(STDOUT_FILENO);
	sptr->saved_stdin = dup(STDIN_FILENO);
	sptr->exit_code = 1;
	g_status = 0;
	g_echo_flag = 0;
	*cmd = 0;
	*cmds = 0;
}

void
	launch_cmd(char **cmds, t_shell *sptr)
{
	int			cmd_idx;

	cmd_idx = -1;
	while (cmds && cmds[++cmd_idx])
	{
		if (cmds[cmd_idx] != NULL)
			parse_command(sptr, cmds[cmd_idx]);
	}
}

void
	check_echo_status(const char *cmd)
{
	int			index;
	int			size;

	size = ft_strlen(cmd) - ECHO_STATUS_SIZE;
	index = 0;
	while (index < size)
	{
		if (ft_strncmp(&(cmd[index]), ECHO_STATUS, ECHO_STATUS_SIZE) == 0)
		{
			g_echo_flag += 1;
			break ;
		}
		index += 1;
	}
	if (g_echo_flag == 2)
	{
		g_status = 0;
		g_echo_flag = 0;
	}
}

int
	check_piped_exit(char **cmd)
{
	int			is_pipe;
	int			index;
	int			size;
	char		*temp;

	if (cmd == (char **)0 || *cmd == (char *)0)
		return (0);
	if ((is_pipe = find_char_in_str('|', *cmd)) == -1)
		return (0);
	index = 0;
	size = ft_strlen(*cmd) - ft_strlen("exit");
	while (index < size)
	{
		if (ft_strncmp(&((*cmd)[index]), "exit", 4) == 0)
		{
			temp = ft_strdup("");
			free_ptr(cmd);
			*cmd = temp;
			return (1);
		}
		index += 1;
	}
	return (0);
}
