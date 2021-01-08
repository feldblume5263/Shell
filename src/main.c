/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyeo <kyeo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 20:20:48 by kyeo              #+#    #+#             */
/*   Updated: 2021/01/08 21:20:52 by kyeo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void
	export(t_shell *sptr, char **args)
{
}

void
	command_parser(t_shell *sptr, const char *input)
{
	int				data_index;
	char			**data;

	data = ft_split(input, ' ');
	if (ft_strncmp(data[0], "env", 3) == 0)
	{
	}
	else if (ft_strncmp(data[0], "unset", 5) == 0)
	{
		unset(sptr, &(data[1]));
	}
	else if (ft_strncmp(data[0], "export", 6) == 0)
	{
		export(sptr, &(data[1]));
	}
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
	env(&shell);
	printf("======================\n\n");
	printf("======================\n\n");
	command_parser(&shell, "unset WATER FIRE");
	env(&shell);
	return (0);
}
