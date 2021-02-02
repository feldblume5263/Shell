/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyeo <kyeo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 13:12:36 by kyeo              #+#    #+#             */
/*   Updated: 2021/02/02 14:35:21 by kyeo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void
	sig_handler(int signo)
{
	if (signo == SIGINT)
	{
		g_status = 1;
		write(2, "\n", 1);
		print_prompt();
		g_prompt_status = 0;
	}
	else if (signo == SIGQUIT)
	{
		ft_putstr_fd("\b\b", 1);
	}
}

void
	sig_init(void)
{
	signal(SIGQUIT, sig_handler);
	signal(SIGINT, sig_handler);
	g_prompt_status = 1;
}
