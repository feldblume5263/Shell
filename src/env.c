/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyeo <kyeo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 18:02:01 by kyeo              #+#    #+#             */
/*   Updated: 2021/01/08 18:02:19 by kyeo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void
	env(t_shell *sptr)
{
	t_env			*head;

	head = sptr->env;
	while (sptr->env)
	{
		write(1, sptr->env->name, ft_strlen(sptr->env->name));
		write(1, "=", 1);
		write(1, sptr->env->data, ft_strlen(sptr->env->data));
		write(1, "\n", 1);
		sptr->env = sptr->env->next;
	}
	sptr->env = head;
}
