/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhpark <junhpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 20:20:48 by kyeo              #+#    #+#             */
/*   Updated: 2021/01/12 20:35:19 by kyeo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void
	command_parser(t_shell *sptr, const char *input)
{
	int				data_index;
	char			**data;

	if (*input == '\0')
		return ;
	data = ft_split(input, ' ');
	// if (ft_strncmp(data[0], "echo", 4) == 0)
	// 	builtins_echo(sptr, input);
	// else
	if (ft_strncmp(data[0], "env", 3) == 0)
		builtins_env(sptr->env, 0);
	else if (ft_strncmp(data[0], "unset", 5) == 0)
		builtins_unset(sptr, &(data[1]));
	else if (ft_strncmp(data[0], "export", 6) == 0)
		builtins_export(sptr, &(data[1]));
	else if (ft_strncmp(data[0], "pwd", 3) == 0)
		builtins_pwd(sptr);
	else if (ft_strncmp(data[0], "cd", 2) == 0)
		builtins_cd(sptr, data[1]);
	data_index = 0;
	while (data[data_index])
	{
		free(data[data_index]);
		data_index += 1;
	}
	free(data);
}

int
	main(int argc, char **argv, char **envp)
{
	int				ret;
	char			*cmd;
	t_shell			shell;

	if (argc != 1 || (ft_strncmp(argv[0], "./a.out", 7) != 0))
	{
		// error handling - invalid arg
		printf("ERROR OCCURED - ARGC MUST BE 1\n");
	}
	if ((ret = init_env(&(shell.env), envp)) < 0)
	{
		// error handling - must free node data
		printf("ERROR OCCURED - INIT ENV FAILED\n");
	}
	cmd = (char *)0;
	prompt(&shell, &cmd);
	return (0);
}
