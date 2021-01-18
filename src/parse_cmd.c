/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhpark <junhpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 22:31:32 by junhpark          #+#    #+#             */
/*   Updated: 2021/01/18 18:19:52 by junhpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void			dispence_command(t_shell *sptr, char **data, char *raw)
{
	int			idx;

	(void) raw;
	if (ft_strlen(data[0]) == 4 && ft_strncmp(data[0], "echo", 4) == 0)
	{
		write(1, "run echo\n", 9);
		return ;
	}
	idx = 0;
	while (data[++idx])
	{
		delete_subs(&(data[idx]));
		write(1, data[idx], ft_strlen(data[idx]));
	}
	if (ft_strlen(data[0]) == 3 && ft_strncmp(data[0], "env", 3) == 0)
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
	int			idx;

	idx = 0;
	data = ft_split(raw, (char)SPACE);
	delete_subs(&(data[0]));
	dispence_command(sptr, data, raw);
	while (data[idx])
	{
		free(data[idx]);
		data[idx] = 0;
		idx++;
	}
	free(data);
	data = 0;
}