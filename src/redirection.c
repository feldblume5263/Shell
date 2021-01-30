/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhpark <junhpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/24 11:32:20 by junhpark          #+#    #+#             */
/*   Updated: 2021/01/30 18:24:01 by kyeo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int				redirect_in(char *redir)
{
	int			infd;
	char		*infile;

	if ((infile = redir) == NULL)
		return (-1);
	if (find_redir(redir) > 0)
		return (-1);
	if ((infd = open(infile, O_RDONLY)) == -1)
		return (-1);
	if (dup2(infd, STDIN_FILENO) == -1)
	{
		close(infd);
		return (-1);
	}
	return (close(infd));
}

int				redirect_out_d(char *redir)
{
	int			outfd;
	char		*outfile;

	if ((outfile = redir) == NULL)
		return (-1);
	if (find_redir(redir) > 0)
		return (-1);
	if ((outfd = open(outfile, O_RDWR | O_CREAT | O_APPEND, 0666)) == -1)
		return (-1);
	if (dup2(outfd, STDOUT_FILENO) == -1)
	{
		close(outfd);
		return (-1);
	}
	return (close(outfd));
}

int				redirect_out(char *redir)
{
	int			outfd;
	char		*outfile;

	if ((outfile = redir) == NULL)
		return (-1);
	if (find_redir(redir) > 0)
		return (-1);
	if ((outfd = open(outfile, O_RDWR | O_CREAT | O_TRUNC, 0666)) == -1) // *수정
		return (-1);
	if (dup2(outfd, STDOUT_FILENO) == -1)
	{
		close(outfd);
		return (-1);
	}
	return (close(outfd));
}

int				handle_redir_error(char **redir)
{
	int			idx;

	idx = 0;
	while (redir[idx])
	{

		if (idx > 0 && ft_strncmp(redir[idx - 1], ">>", 2) == 0) // *수정
		{
			if (find_redir(redir[idx]) > 0)
				return (-1);
		}
	 	else if (idx > 0 && ft_strncmp(redir[idx - 1], ">", 1) == 0) //*수정
		{
			if (find_redir(redir[idx]) > 0)
				return (-1);
		}
		else if (idx > 0 && ft_strncmp(redir[idx - 1], "<", 1) == 0)
		{
			if (find_redir(redir[idx]) > 0)
				return (-1);
		}
		idx++;
	}
	return (1);
}

int				redirection(char **redir)
{
	int			idx;
	int			error_code;

	if (redir == (char **)NULL || *redir == (char *)NULL)
		return (1);
	idx = 0;
	while (redir[idx])
	{
		if (idx > 0 && ft_strncmp(redir[idx - 1], ">>", 2) == 0) // *수정
			error_code = redirect_out_d(redir[idx]);
		else if (idx > 0 && ft_strncmp(redir[idx - 1], ">", 1) == 0) // *수정
			error_code = redirect_out(redir[idx]);
		else if (idx > 0 && ft_strncmp(redir[idx - 1], "<", 1) == 0)
			error_code = redirect_in(redir[idx]);
		idx++;
	}
	return (1);
}
