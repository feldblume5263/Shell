/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhpark <junhpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 20:20:48 by kyeo              #+#    #+#             */
/*   Updated: 2021/02/01 22:16:11 by junhpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int
	main(int argc, char **argv, char **envp)
{
	int				ret;
	t_shell			shell;

	if (argc != 1 || (ft_strncmp(argv[0], "minishell", 7) != 0))
		printf("ERROR OCCURED - ARGC MUST BE 1\n");
	if ((ret = init_env(&(shell.env), envp)) < 0)
		printf("ERROR OCCURED - INIT ENV FAILED\n");
	g_status = 0;
	shell.envp = &envp;
	prompt(&shell);
	return (0);
}
