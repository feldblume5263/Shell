/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhpark <junhpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 20:20:48 by kyeo              #+#    #+#             */
/*   Updated: 2021/01/27 22:09:27 by kyeo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	g_status = 1;
	cmd = (char *)0;
	prompt(&shell);
	return (0);
}
