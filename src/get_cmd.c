/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhpark <junhpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 14:48:54 by junhpark          #+#    #+#             */
/*   Updated: 2021/01/27 21:04:41 by kyeo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			cmd_join(char **cmd, char *buf, int size)
{
	int		i;
	int		j;
	char	*new;

	if (!(new = malloc(sizeof(char) * (size + 1))))
		return (-1);
	i = 0;
	while (*cmd != (char *)0 && (*cmd)[i])
	{
		new[i] = (*cmd)[i];
		i++;
	}
	j = 0;
	while (buf[j])
	{
		new[i + j] = buf[j];
		j++;
	}
	new[i + j] = '\0';
	if (*cmd != (char *)0)
		free(*cmd);
	*cmd = new;
	return (1);
}

int			make_cmd(char buf[], char **cmd)
{
	int		size;

	if (*cmd == (char *)0)
		size = ft_strlen(buf);
	else
		size = ft_strlen(*cmd) + ft_strlen(buf);
	cmd_join(cmd, buf, size);
	return (size);
}

void		getcmd(char **cmd)
{
	int		ret;
	char	buf[4096 + 1];
	int		idx;
	int		nl;

	nl = 0;
	ft_bzero(buf, 4097);
	idx = 0;
	while ((ret = read(0, buf, 4096)) > 0)
	{
		buf[ret] = '\0';
		idx = -1;
		while (buf[++idx])
		{
			if (buf[idx] == '\n')
				nl = 1;
		}
		make_cmd(buf, cmd);
		ft_bzero(buf, 4097);
		if (nl == 1)
			break ;
	}
	if (idx == 0 && ret == 0)
		*cmd = NULL;
}
