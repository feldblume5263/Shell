/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhpark <junhpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 21:20:10 by junhpark          #+#    #+#             */
/*   Updated: 2021/01/13 01:50:29 by junhpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			builtins_echo(t_shell *sptr, char **args)
{
	char		**pureargv;
	int			idx;
	int			chunk_idx;

	idx = 0;
	pureargv = ft_split(*args, ' ');
	(void)sptr;
	if (ft_strncmp(pureargv[0], "-n", 2) == 0 && ft_strlen(pureargv[0]) == 2)
	{
		while ((*args)[idx] && (*args)[idx] != 'n')
			idx++;
		idx++;
		write(1, &((*args)[idx]), ft_strlen(&((*args)[idx])));
		chunk_idx = 1;
		while (args[chunk_idx])
		{
			write(1, args[chunk_idx], ft_strlen(args[chunk_idx]));
			chunk_idx++;
		}
	}
	else
	{
		chunk_idx = 0;
		while (args[chunk_idx])
		{
			write(1, args[chunk_idx], ft_strlen(args[chunk_idx]));
			chunk_idx++;
		}
		write(1, "\n", 1);
	}
}
