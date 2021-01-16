/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhpark <junhpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 00:49:12 by junhpark          #+#    #+#             */
/*   Updated: 2021/01/16 16:57:51 by junhpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	free(p);
	p = 0;
}

void		safe_free_temp(char **p)
{
	free(*p);
	*p = 0;
}
