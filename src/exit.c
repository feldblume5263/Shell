/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhpark <junhpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 21:57:19 by kyeo              #+#    #+#             */
/*   Updated: 2021/02/02 20:18:55 by kyeo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int
	is_str_num(const char *str)
{
	int			index;
	int			size;

	if (str == 0)
		return (1);
	size = ft_strlen(str);
	index = 0;
	while (index < size)
	{
		if (ft_isdigit(str[index]) == 0)
			return (0);
		index += 1;
	}
	return (1);
}

void
	builtins_exit(t_shell *sptr, char **args)
{
	(void)sptr;
	write(1, "exit\n", 5);
	if (args[1] && !is_str_num(args[1]))
	{
		write(2, "mini: exit: ", 6);
		write(2, args[1], ft_strlen(args[1]));
		write(2, ": ", 2);
		write(2, "numeric argument required\n", 26);
	}
	sptr->exit_code = 0;
}
