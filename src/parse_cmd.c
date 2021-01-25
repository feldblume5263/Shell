/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhpark <junhpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 22:31:32 by junhpark          #+#    #+#             */
/*   Updated: 2021/01/25 16:14:13 by kyeo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			dispence_command(t_shell *sptr, char **data)
{
	int			idx;

	idx = 0;
	while (data[idx])
	{
		printf("DATA[%d]: %s\n", idx, data[idx]);
		idx += 1;
	}
	idx = 0;
	if (!(data[idx]))
		return ;
	while (data[++idx])
		delete_subs(&(data[idx]));
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
	else
		exec(sptr, data);
}

void			parse_command(t_shell *sptr, char *raw)
{
	char		**data;
	char		**redir;
	int			saved_stdout;

	printf("RAW: %s\n", raw);
	saved_stdout = dup(STDOUT_FILENO);
	data = ft_split(raw, (char)SPACE);
	parse_redirection(&data, &redir);
	delete_subs(&(data[0]));
	if (redirection(redir) < 0)
		return ;
	dispence_command(sptr, data);
	free_double_ptr((void ***)&data);
	free_double_ptr((void ***)&redir);
	dup2(saved_stdout, STDOUT_FILENO);
}
