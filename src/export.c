/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyeo <kyeo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 16:25:40 by kyeo              #+#    #+#             */
/*   Updated: 2021/01/10 16:30:21 by kyeo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env
	*dup_all_env(t_env *original)
{
	t_env			*org_head;
	t_env			*dup_head;
	t_env			*dup_temp;
	t_env			*duplicate;

	org_head = original;
	init_env_node(&duplicate);
	dup_head = duplicate;
	duplicate->name = ft_strdup(original->name);
	duplicate->data = ft_strdup(original->data);
	original = original->next;
	while (original)
	{
		dup_temp = duplicate;
		init_env_node(&duplicate);
		duplicate->name = ft_strdup(original->name);
		duplicate->data = ft_strdup(original->data);
		dup_temp->next = duplicate;
		duplicate->prev = dup_temp;
		original = original->next;
	}
	original = org_head;
	return (dup_head);
}

void
	sort_env(t_env *eptr)
{
	t_env			temp;
	t_env			*head;
	t_env			*cmp;

	head = eptr;
	while (eptr->next)
	{
		cmp = eptr->next;
		while (cmp)
		{
			if (ft_strncmp(eptr->name, cmp->name, ft_strlen(cmp->name)) > 0)
			{
				temp.name = eptr->name;
				temp.data = eptr->data;
				eptr->name = cmp->name;
				eptr->data = cmp->data;
				cmp->name = temp.name;
				cmp->data = temp.data;
			}
			cmp = cmp->next;
		}
		eptr = eptr->next;
	}
	eptr = head;
}

void
	builtins_export(t_shell *sptr, char **args)
{
	t_env			*dup_env;

	if (args == (char **)0)
	{
		dup_env = dup_all_env(sptr->env);
		sort_env(dup_env);
		builtins_env(dup_env, 1);
		free_env(dup_env);
	}
}
