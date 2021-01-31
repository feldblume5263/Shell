/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhpark <junhpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 21:57:19 by kyeo              #+#    #+#             */
/*   Updated: 2021/01/31 17:22:58 by kyeo             ###   ########.fr       */
/*   Updated: 2021/01/30 20:29:04 by junhpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void
	builtins_exit(t_shell *sptr, char **args)
{
	(void)args;
	(void)sptr;
	//g_status = 0;
	sptr->exit_code = 0;
	exit(0);
}
