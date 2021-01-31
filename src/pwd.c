/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyeo <kyeo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 20:30:29 by kyeo              #+#    #+#             */
/*   Updated: 2021/01/31 15:11:54 by kyeo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void
	builtins_pwd(t_shell *sptr)
{
	t_env			*temp;

	temp = find_env_by_name(sptr->env, "PWD");
	write(1, temp->data, ft_strlen(temp->data));
	write(1, "\n", 1);
}
