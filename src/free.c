/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhpark <junhpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 20:20:17 by kyeo              #+#    #+#             */
/*   Updated: 2021/01/31 17:23:25 by kyeo             ###   ########.fr       */
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
	t_env		*temp;

	if (env == (t_env *)0)
		return ;
	while (env)
	{
		temp = env->next;
		free_env_node(env);
		env = temp;
	}
}

void		free_ptr(char **ptr)
{
	if (*ptr)
	{
		free(*ptr);
		*ptr = NULL;
	}
}

void		free_double_ptr(void ***dptr)
{
	int			index;

	index = 0;
	while (*dptr && (*dptr)[index])
	{
		free((*dptr)[index]);
		(*dptr)[index] = NULL;
		index += 1;
	}
	if (*dptr)
	{
		free(*dptr);
		*dptr = NULL;
	}
}
