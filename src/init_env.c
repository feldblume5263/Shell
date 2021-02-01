/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyeo <kyeo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 00:54:36 by kyeo              #+#    #+#             */
/*   Updated: 2021/01/10 16:23:17 by kyeo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int
	find_char_in_str(const char c, const char *str)
{
	int				str_index;

	if (str == (const char *)0)
		return (-1);
	str_index = 0;
	while (str[str_index])
	{
		if (str[str_index] == c)
			return (str_index);
		str_index += 1;
	}
	if (str[str_index] == c)
		return (str_index);
	return (-1);
}

void
	copy_until_end(char **dest, const char *start, const char end)
{
	int				index;

	index = 0;
	while (start[index] != end)
	{
		(*dest)[index] = (char)start[index];
		index += 1;
	}
	(*dest)[index] = '\0';
}

int
	make_env_node(t_env **nptr, char *env_raw_data)
{
	int				name_size;
	int				data_size;

	name_size = find_char_in_str('=', env_raw_data);
	data_size = find_char_in_str('\0', &(env_raw_data[name_size + 1]));
	if (((*nptr)->name = malloc(sizeof(char) * (name_size + 1))) == (char *)0)
		return (MEM_ERROR);
	if (((*nptr)->data = malloc(sizeof(char) * (data_size + 1))) == (char *)0)
		return (MEM_ERROR);
	copy_until_end(&((*nptr)->name), env_raw_data, '=');
	copy_until_end(&((*nptr)->data), &(env_raw_data[name_size + 1]), '\0');
	return (0);
}

int
	init_env_node(t_env **nptr)
{
	if ((*nptr = malloc(sizeof(struct s_env) * 1)) == (struct s_env *)0)
		return (MEM_ERROR);
	(*nptr)->name = (char *)0;
	(*nptr)->data = (char *)0;
	(*nptr)->next = (struct s_env *)0;
	(*nptr)->prev = (struct s_env *)0;
	return (0);
}

int
	init_env(t_env **head, char **envp)
{
	int				ret;
	int				loop_index;
	t_env			*node;
	t_env			*temp;

	loop_index = 1;
	if (envp == (char **)0)
		return (ARG_ERROR);
	if ((ret = init_env_node(&node)) < 0 ||\
		(ret = make_env_node(&node, envp[loop_index - 1]) < 0))
		return (ret);
	*head = node;
	while (envp[loop_index])
	{
		temp = node;
		if ((ret = init_env_node(&node)) < 0 ||\
			(ret = make_env_node(&node, envp[loop_index]) < 0))
			return (ret);
		temp->next = node;
		node->prev = temp;
		loop_index += 1;
	}
	return (0);
}
