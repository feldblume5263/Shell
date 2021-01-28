/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 18:02:01 by kyeo              #+#    #+#             */
/*   Updated: 2021/01/28 20:07:57 by kyeo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void
	connect_new_env_node(t_env **new, t_env **eptr)
{
	(*new)->next = *eptr;
	(*eptr)->prev = (*new);
	(*eptr) = (*new);
}

void
	builtins_env(t_env *eptr, const int export_option)
{
	t_env			*head;

	head = eptr;
	while (export_option == 0 && eptr)
	{
		write(1, eptr->name, ft_strlen(eptr->name));
		write(1, "=", 1);
		write(1, eptr->data, ft_strlen(eptr->data));
		write(1, "\n", 1);
		eptr = eptr->next;
	}
	while (export_option && eptr)
	{
		write(1, "declare -x ", 11);
		write(1, eptr->name, ft_strlen(eptr->name));
		write(1, "=", 1);
		write(1, "\"", 1);
		write(1, eptr->data, ft_strlen(eptr->data));
		write(1, "\"", 1);
		write(1, "\n", 1);
		eptr = eptr->next;
	}
	eptr = head;
	exit(0);
}
exit(0);
