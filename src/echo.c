/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhpark <junhpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 18:30:41 by junhpark          #+#    #+#             */
/*   Updated: 2021/02/02 19:56:48 by junhpark         ###   ########.fr       */
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
	print_env_detail(t_shell *sptr, char **remake)
{
	t_env	*temp;

	temp = 0;
	if (!((*remake)[0]))
		write(1, "$", 1);
	else if ((*remake)[0] && (*remake)[0] == '?')
	{
		ft_putnbr_fd(g_status, 1);
		g_status = 0;
		if ((*remake)[1] != (char)ENV)
			write(1, &((*remake)[1]), ft_strlen(&((*remake)[1])));
		else
			print_env(sptr, &((*remake)[1]));
	}
	else if ((temp = find_env_by_name(sptr->env, (*remake))) == (t_env *)0)
		return ;
	else
		write(1, temp->data, ft_strlen(temp->data));
}

void
	print_env(t_shell *sptr, char *env)
{
	char	*remake;
	int		size;

	size = 1;
	while (env[size] && env[size] != (char)ENV && env[size] != '=')
		size++;
	remake = (char *)malloc(sizeof(char) * size + 1);
	size = 1;
	while (env[size] && env[size] != (char)ENV && env[size] != '=')
	{
		remake[size - 1] = env[size];
		size++;
	}
	remake[size - 1] = '\0';
	print_env_detail(sptr, &remake);
	free(remake);
}

void
	print_with_opt(t_shell *sptr, char **data, int num)
{
	int			chunk_idx;
	int			idx;

	chunk_idx = -1;
	while (data[++chunk_idx])
	{
		idx = num;
		while (data[chunk_idx][idx] && data[chunk_idx][idx] != (char)ENV)
		{
			if (data[chunk_idx][0] == '#')
				return ;
			write(1, &(data[chunk_idx][idx]), 1);
			idx++;
		}
		if (data[chunk_idx][idx] && data[chunk_idx][idx] == (char)ENV)
		{
			print_env(sptr, &(data[chunk_idx][idx++]));
			while (data[chunk_idx][idx] && data[chunk_idx][idx]
				!= (char)ENV && data[chunk_idx][idx] != '=')
				idx++;
			print_with_opt(sptr, &(data[chunk_idx]), idx);
		}
		if (!(data[chunk_idx][idx]) && data[chunk_idx + 1])
			write(1, " ", 1);
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
		print_with_opt(sptr, &(data[idx]), 0);
	}
	else
	{
		print_with_opt(sptr, data, 0);
		write(1, "\n", 1);
	}
}
