/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyeo <kyeo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/02 16:08:49 by kyeo              #+#    #+#             */
/*   Updated: 2021/01/03 01:02:43 by kyeo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void
	free_env_node(t_env *need_to_free)
{
	free(need_to_free->name);
	free(need_to_free->data);
	free(need_to_free);
}

void
	connect_prev_and_next(t_env **temp)
{
	(*temp)->next->prev = (*temp)->prev;
	(*temp)->prev->next = (*temp)->next;
}

void
	free_unset_args(char **args)
{
	int			index;

	index = 0;
	while (args && args[index])
	{
		free(args[index]);
		index += 1;
	}
	if (args)
		free(args);
}

int
	unset(const char *arg, t_env *env_copy)
{
	int			index;
	char		**args;
	t_env		*head;

	args = ft_split(arg, ' ');
	head = env_copy;
	index = 0;
	while (args && args[index])
	{
		env_copy = head;
		while (env_copy)
		{
			if ((ft_strncmp(env_copy->name, args[index],\
							ft_strlen(args[index]))) == 0)
			{
				connect_prev_and_next(&env_copy);
				free_env_node(env_copy);
				break ;
			}
			env_copy = env_copy->next;
		}
		index += 1;
	}
	free_unset_args(args);
	return (0);
}
