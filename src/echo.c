/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhpark <junhpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 21:20:10 by junhpark          #+#    #+#             */
/*   Updated: 2021/01/13 19:21:05 by junhpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			echo_with_option(t_shell *sptr, const char *input)
{
	int			idx;

	(void)sptr;
	idx = 4;
	while (input[idx] == ' ')
		idx++;
	idx += 2;
	while (input[idx] == ' ')
		idx++;
	write(1, &(input[idx]), ft_strlen(&(input[idx])));
}

void			echo_without_option(t_shell *sptr, const char *input)
{
	int			idx;

	(void)sptr;
	idx = 4;
	while (input[idx] == ' ')
		idx++;
	write(1, &(input[idx]), ft_strlen(&(input[idx])));
	write(1, "\n", 1);
}

void			builtins_echo(t_shell *sptr, char **args, const char *input)
{
	char		**div_arg;

	div_arg = ft_split(*args, ' ');
	(void)sptr;
	if (ft_strncmp(div_arg[0], "-n", 2) == 0 && ft_strlen(div_arg[0]) == 2)
		echo_with_option(sptr, input);
	else
		echo_without_option(sptr, input);
}
