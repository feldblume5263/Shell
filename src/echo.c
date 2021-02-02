/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhpark <junhpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 18:30:41 by junhpark          #+#    #+#             */
/*   Updated: 2021/02/02 16:02:57 by junhpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int
	is_env_closed(char *str, int idx)
{
	int				lit_q;
	int				start;

	lit_q = 0;
	start = 0;
	while (str[start] && start < idx)
	{
		if (str[start] == (char)LIT_Q)
			lit_q++;
		start++;
	}
	if (lit_q % 2 == 0)
		return (1);
	else
		return (0);
}

void
	print_env(t_shell *sptr, char *env)
{
	t_env	*temp;

	if (!(env[1]))
		write(1, "$", 1);
	else if (env[1] && env[1] == '?')
	{
		ft_putnbr_fd(g_status, 1);
		g_status = 0;
		if (env[2] != (char)ENV)
			write(1, &(env[2]), ft_strlen(&(env[2])));
		else
			print_env(sptr, &(env[2]));
	}
	else if ((temp = find_env_by_name(sptr->env, &(env[1]))) == (t_env *)0)
		return ;
	else
		write(1, temp->data, ft_strlen(temp->data));
}

void
	print_without_opt(t_shell *sptr, char **data)
{
	int			chunk_idx;
	int			idx;

	chunk_idx = 0;
	while (data[chunk_idx])
	{
		idx = 0;
		while (data[chunk_idx][idx] && data[chunk_idx][idx] != (char)ENV)
		{
			if (data[chunk_idx][0] == '#')
			{
				write(1, "\n", 1);
				return ;
			}
			write(1, &(data[chunk_idx][idx]), 1);
			idx++;
		}
		if (data[chunk_idx][idx] && data[chunk_idx][idx] == (char)ENV)
			print_env(sptr, &(data[chunk_idx][idx]));
		if (data[chunk_idx + 1])
			write(1, " ", 1);
		chunk_idx++;
	}
	write(1, "\n", 1);
}

void
	print_with_opt(t_shell *sptr, char **data)
{
	int			chunk_idx;
	int			idx;

	chunk_idx = 0;
	while (data[chunk_idx])
	{
		idx = 0;
		while (data[chunk_idx][idx] && data[chunk_idx][idx] != (char)ENV)
		{
			if (data[chunk_idx][0] == '#')
				return ;
			write(1, &(data[chunk_idx][idx]), 1);
			idx++;
		}
		if (data[chunk_idx][idx] && data[chunk_idx][idx] == (char)ENV)
			print_env(sptr, &(data[chunk_idx][idx]));
		if (data[chunk_idx + 1])
			write(1, " ", 1);
		chunk_idx++;
	}
}

void
	builtins_echo(t_shell *sptr, char **data)
{
	int				idx;

	if (ft_strlen(data[0]) == 2 && ft_strncmp(data[0], "-n", 2) == 0)
	{
		idx = 1;
		while (ft_strlen(data[idx]) == 2 && ft_strncmp(data[idx], "-n", 2) == 0)
			idx++;
		print_with_opt(sptr, &(data[idx]));
	}
	else
		print_without_opt(sptr, data);
}
