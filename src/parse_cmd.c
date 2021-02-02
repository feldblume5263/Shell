/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhpark <junhpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 22:31:32 by junhpark          #+#    #+#             */
/*   Updated: 2021/02/02 15:13:14 by junhpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void
	check_only_space(char **cmd)
{
	int			idx;
	int			count;
	char 		*res;

	idx = 0;
	count = 0;
	while ((*cmd)[idx])
	{
		if ((*cmd)[idx] == ' ')
			count++;
		idx++;
	}
	if (count + 1 == idx)
	{
		free(*cmd);
		res = (char *)malloc(sizeof(char) * 2);
		res[0] = '\n';
		res[1] = '\0';
		*cmd = res;
	}
}

void
	dispence_command(t_shell *sptr, char **data, const int builtins)
{
	if (ft_strlen(data[0]) == 4 && ft_strncmp(data[0], "echo", 4) == 0)
		builtins_echo(sptr, &(data[1]));
	else if (ft_strlen(data[0]) == 3 && ft_strncmp(data[0], "env", 3) == 0)
		builtins_env(sptr->env, 0);
	else if (ft_strlen(data[0]) == 5 && ft_strncmp(data[0], "unset", 5) == 0)
		builtins_unset(sptr, &(data[1]));
	else if (ft_strlen(data[0]) == 6 && ft_strncmp(data[0], "export", 6) == 0)
		builtins_export(sptr, &(data[1]));
	else if (ft_strlen(data[0]) == 3 && ft_strncmp(data[0], "pwd", 3) == 0)
		builtins_pwd(sptr);
	else if (ft_strlen(data[0]) == 2 && ft_strncmp(data[0], "cd", 2) == 0)
		builtins_cd(sptr, data[1]);
	else if (ft_strlen(data[0]) == 4 && ft_strncmp(data[0], "exit", 4) == 0)
		builtins_exit(sptr, data);
	else
		exec(sptr, data);
	if (builtins == 0 || builtins == 2)
		exit(0);
}

void
	init_cdata(t_cmd *dptr)
{
	dptr->cmds_redirected = 0;
	dptr->cmds_index = -1;
}

void
	parse_command(t_shell *sptr, char *raw)
{
	t_cmd		cdata;

	init_cdata(&cdata);
	set_data_with_redirection(&(cdata.pip), &(cdata.cmds_redirected), raw);
	while (cdata.cmds_redirected[++cdata.cmds_index])
	{
		cdata.builtins = is_builtins(cdata.cmds_redirected[cdata.cmds_index]);
		if (cdata.builtins == 0)
			path_join(sptr, cdata.cmds_redirected[cdata.cmds_index]);
		if (cdata.cmds_redirected[cdata.cmds_index + 1])
			pipe(cdata.pip.new_fds);
		cdata.pid = fork();
		if (cdata.pid == 0)
		{
			pipe_child(&cdata);
			if (cdata.builtins != 1)
				dispence_command(sptr, cdata.cmds_redirected[cdata.cmds_index],\
						cdata.builtins);
			else
				exit(0);
		}
		else
			pipe_parent(sptr, &cdata);
	}
	pipe_end(&cdata, &(cdata.pip), cdata.cmds_index);
}
