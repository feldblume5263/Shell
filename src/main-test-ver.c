/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyeo <kyeo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/31 21:11:51 by kyeo              #+#    #+#             */
/*   Updated: 2021/01/02 16:09:52 by kyeo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void
	print_env(t_env *env_copy)
{
	while (env_copy)
	{
		write(1, env_copy->name, strlen(env_copy->name));
		write(1, "\n", 1);
		write(1, env_copy->data, strlen(env_copy->data));
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
	return (ret);
}
