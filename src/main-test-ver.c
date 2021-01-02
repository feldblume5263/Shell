/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main-test-ver.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyeo <kyeo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/31 21:11:51 by kyeo              #+#    #+#             */
/*   Updated: 2021/01/03 00:33:27 by kyeo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

void
	print_env(t_env *env_copy)
{
	while (env_copy)
	{
		write(1, env_copy->name, ft_strlen(env_copy->name));
		write(1, "\n", 1);
		write(1, env_copy->data, ft_strlen(env_copy->data));
		write(1, "\n\n", 2);
		env_copy = env_copy->next;
	}
}

int
	main(int argc, char **argv, char **env)
{
	int			ret;
	t_shell		shell;

	(void)argc;
	(void)argv;
	if ((ret = init_env(env, &(shell.env))) < 0)
		return (ret);
	print_env(shell.env);
	printf("-----------------\n");
	unset("WATER FIRE", shell.env);
	print_env(shell.env);
	printf("-----------------\n");
	return (ret);
}
