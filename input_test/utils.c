/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhpark <junhpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 00:49:12 by junhpark          #+#    #+#             */
/*   Updated: 2021/01/17 22:55:14 by junhpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../include/libft.h"
# include <limits.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>

int				is_closed(char *str, int idx)
{
	int			big_q;
	int			lit_q;
	int			start;

	big_q = 0;
	lit_q = 0;
	start = 0;
	while (str[start] && start <= idx)
	{
		if (str[start] == '"')
			big_q++;
		else if (str[start] == '\'')
			lit_q++;
		start++;
	}
	if (lit_q % 2 == 0 && big_q % 2 == 0)
		return (1);
	else
		return (0);
}

void		safe_free_double(char **p)
{
	int		idx;
	int		size;

	size = 0;
	while (p[size])
		size++;
	idx = 0;
	while (idx < size)
	{
		free(p[idx]);
		p[idx] = 0;
		idx++;
	}
	free(p);
	p = 0;
}

void		safe_free(char *p)
{
	if (p)
	{
		free(p);
		p = 0;
	}
}

void		safe_free_temp(char **p)
{
	if (*p)
	{
		free(*p);
		*p = 0;
	}
}
