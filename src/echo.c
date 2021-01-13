/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhpark <junhpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 21:20:10 by junhpark          #+#    #+#             */
/*   Updated: 2021/01/13 19:39:23 by junhpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			echo_with_option(t_shell *sptr, const char *input)
{
	int			idx;
	int			nl_idx;
	char		*input_cp;

	(void)sptr;
	input_cp = ft_strdup(input);
	idx = 4;
	while (input_cp[idx] == ' ')
		idx++;
	idx += 2;
	while (input_cp[idx] == ' ')
		idx++;
	nl_idx = 0;
	while (input_cp[nl_idx])
		nl_idx++;
	input_cp[--nl_idx] = '\0';
	write(1, &(input_cp[idx]), ft_strlen(&(input_cp[idx])));
	free(input_cp);
}

void			echo_without_option(t_shell *sptr, const char *input)
{
	int			idx;

	(void)sptr;

	idx = 4;
	while (input[idx] == ' ')
		idx++;
	write(1, &(input[idx]), ft_strlen(&(input[idx])));
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
