/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyeo <kyeo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 18:00:42 by kyeo              #+#    #+#             */
/*   Updated: 2021/01/30 18:56:24 by kyeo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void
	delete_env_node(t_env **eptr, const char *env_name)
{
	t_env			*head;

	head = *eptr;
	while (*eptr)
	{
		if (ft_strncmp((*eptr)->name, env_name, ft_strlen(env_name)) == 0)
		{
			if ((*eptr) == head)
				head = head->next;
			if ((*eptr)->prev)
				(*eptr)->prev->next = (*eptr)->next;
			if ((*eptr)->next)
				(*eptr)->next->prev = (*eptr)->prev;
			free((*eptr)->name);
			free((*eptr)->data);
			(*eptr)->next = (struct s_env *)0;
			(*eptr)->prev = (struct s_env *)0;
			free(*eptr);
			*eptr = (struct s_env *)0;
			*eptr = head;
			break ;
		}
		*eptr = (*eptr)->next;
	}
	*eptr = head;
}

void
	builtins_unset(t_shell *sptr, char **args)
{
	int				arg_index;

	arg_index = 0;
	while (args && args[arg_index])
	{
		delete_env_node(&(sptr->env), args[arg_index]);
		arg_index += 1;
	}
}
