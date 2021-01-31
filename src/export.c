/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyeo <kyeo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 16:25:40 by kyeo              #+#    #+#             */
/*   Updated: 2021/01/31 15:11:56 by kyeo             ###   ########.fr       */
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

t_env
	*find_env_by_name(t_env *head, const char *name)
{
	t_env			*temp;

	temp = head;
	while (temp)
	{
		if (ft_strncmp(name, temp->name, ft_strlen(name)) == 0)
			return (temp);
		temp = temp->next;
	}
	return ((t_env *)0);
}

void
	export_with_null_arg(t_env *original)
{
	t_env			*duplicate;

	duplicate = dup_all_env(original);
	sort_env(duplicate);
	builtins_env(duplicate, 1);
	free_all_env(duplicate);
}

void
	builtins_export(t_shell *sptr, char **args)
{
	int				arg_index;
	t_env			*new_env;
	t_env			*temp;

	if (*args == (char *)0)
		export_with_null_arg(sptr->env);
	arg_index = 0;
	while (args[arg_index])
	{
		if (find_char_in_str('=', args[arg_index]) != -1)
		{
			init_env_node(&new_env);
			make_env_node(&new_env, args[arg_index]);
			if ((temp = find_env_by_name(sptr->env, new_env->name))\
					!= (t_env *)0)
			{
				free(temp->data);
				temp->data = ft_strdup(new_env->data);
				free_env_node(new_env);
			}
			else
				connect_new_env_node(&new_env, &(sptr->env));
		}
		arg_index += 1;
	}
}
