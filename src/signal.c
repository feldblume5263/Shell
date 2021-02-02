/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyeo <kyeo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 13:12:36 by kyeo              #+#    #+#             */
/*   Updated: 2021/02/02 15:26:56 by kyeo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void
	child_sig_handler(int signo)
{
	if (signo == SIGINT)
	{
		wirte(1, "\n", 1);
		signal(SIGINT, child_sig_handler);
	}
}

void
	sig_handler(int signo)
{
	if (signo == SIGINT)
	{
		g_status = 1;
		write(2, "\n", 1);
		print_prompt();
		signal(SIGINT, sig_handler);
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
}
