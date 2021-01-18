/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhpark <junhpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 17:43:48 by junhpark          #+#    #+#             */
/*   Updated: 2021/01/18 18:32:17 by junhpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		divide_cmds(char ***cmds, char **cmd)
{
	refine_cmd(cmd);
	(*cmds) = ft_split(*cmd, (char)DIV);
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
		divide_cmds(&cmds, &cmd);
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
