/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyeo <kyeo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 18:02:01 by kyeo              #+#    #+#             */
/*   Updated: 2021/01/10 00:46:00 by kyeo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void
	env(t_env *eptr)
{
	t_env			*head;

	head = eptr;
	while (eptr)
	{	
		write(1, eptr->name, ft_strlen(eptr->name));
		write(1, "=", 1);
		write(1, eptr->data, ft_strlen(eptr->data));
		write(1, "\n", 1);
		eptr = eptr->next;
	}
	eptr = head;
}
