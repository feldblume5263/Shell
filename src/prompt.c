/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhpark <junhpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 17:43:48 by junhpark          #+#    #+#             */
/*   Updated: 2021/02/02 20:21:19 by kyeo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void
	divide_cmds(char ***cmds, char **cmd)
{
	if (*cmd != NULL)
	{
		check_only_space(cmd);
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
	prompt(t_shell *sptr)
{
	char	**cmds;
	char	*cmd;
	char	*temp;

	prepare_std(sptr, &cmd, &cmds);
	while (sptr->exit_code)
	{
		sig_init();
		print_prompt();
		getcmd(&cmd);
		if (cmd == NULL)
			break ;
		check_piped_exit(&cmd);
		check_echo_status(cmd);
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
