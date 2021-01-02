/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyeo <kyeo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/01 00:38:48 by kyeo              #+#    #+#             */
/*   Updated: 2021/01/03 00:30:52 by kyeo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int
	make_env_node(char *env_data, t_env **node)
{
	int			index;
	int			name_size;
	int			data_size;

	if (!((*node) = malloc(sizeof(struct s_env) * 1)))
		return (-2);
	name_size = 0;
	while (env_data[name_size] != '=')
		name_size += 1;
	data_size = ft_strlen(env_data) - name_size;
	if (!((*node)->name = malloc(sizeof(char) * (name_size + 1))))
		return (-2);
	index = -1;
	while (++index < name_size)
		((*node)->name)[index] = env_data[index];
	((*node)->name)[index] = '\0';
	if (!((*node)->data = malloc(sizeof(char) * (data_size + 1))))
		return (-2);
	while (env_data[++index])
		((*node)->data)[index - name_size - 1] = env_data[index];
	((*node)->data)[index - name_size - 1] = '\0';
	(*node)->prev = (struct s_env *)0;
	(*node)->next = (struct s_env *)0;
	return (0);
}

int
	init_env(char **env, t_env **env_copy)
{
	int			ret;
	int			env_index;
	t_env		*node;
	t_env		*head;

	if (env == (char **)0)
		return (-1);
	env_index = 1;
	if ((ret = make_env_node(env[env_index - 1], &node)) < 0)
		return (ret);
	head = node;
	*env_copy = node;
	while (env[env_index])
	{
		if ((ret = make_env_node(env[env_index], &node) < 0))
			return (ret);
		node->prev = *env_copy;
		(*env_copy)->next = node;
		*env_copy = (*env_copy)->next;
		env_index += 1;
	}
	*env_copy = head;
	return (0);
}
