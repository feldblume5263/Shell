/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyeo <kyeo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 20:20:17 by kyeo              #+#    #+#             */
/*   Updated: 2021/01/10 20:20:34 by kyeo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void
	free_env_node(t_env *node)
{
	if (node->name)
	{
		free(node->name);
		node->name = (char *)0;
	}
	if (node->data)
	{
		free(node->data);
		node->data = (char *)0;
	}
	if (node)
	{
		node->next = (struct s_env *)0;
		node->prev = (struct s_env *)0;
		free(node);
		node = (struct s_env *)0;
	}
}

void
	free_all_env(t_env *env)
{
	t_env			*temp;

	if (env == (t_env *)0)
		return ;
	while (env)
	{
		temp = env->next;
		free_env_node(env);
		env = temp;
	}
}
