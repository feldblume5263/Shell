/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_cmd_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhpark <junhpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/31 16:57:45 by kyeo              #+#    #+#             */
/*   Updated: 2021/02/02 01:55:24 by kyeo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int
	is_builtins(char **data)
{
	if ((ft_strlen(data[0]) == 5 && ft_strncmp(data[0], "unset", 5) == 0 &&\
			data[1] != (char *)0) ||\
		(ft_strlen(data[0]) == 6 && ft_strncmp(data[0], "export", 6) == 0 &&\
		data[1] != (char *)0) ||\
		(ft_strlen(data[0]) == 2 && ft_strncmp(data[0], "cd", 2) == 0) ||\
		(ft_strlen(data[0]) == 4 && ft_strncmp(data[0], "exit", 4) == 0))
		return (1);
	else if ((ft_strlen(data[0]) == 4 && ft_strncmp(data[0], "echo", 4) == 0)\
	|| ((ft_strlen(data[0]) == 3 && ft_strncmp(data[0], "env", 3) == 0)) ||\
	((ft_strlen(data[0]) == 3 && ft_strncmp(data[0], "pwd", 3) == 0)) ||\
	((ft_strlen(data[0]) == 6 && ft_strncmp(data[0], "export", 6) == 0 &&\
	!data[1])) ||\
	(ft_strlen(data[0]) == 5 && ft_strncmp(data[0], "unset", 5) == 0 &&\
	!data[1]))
		return (2);
	return (0);
}

int
	count_char_in_str(const char *string, const char c)
{
	int			index;
	int			number_of_characters;

	index = 0;
	number_of_characters = 0;
	while (string && string[index])
	{
		if (string[index] == c)
			number_of_characters += 1;
		index += 1;
	}
	return (number_of_characters);
}

void
	delete_sub_in_cmd(char **data)
{
	int			index;

	index = 0;
	while (data[index])
	{
		delete_subs(&(data[index]));
		index += 1;
	}
}

int
	set_data_with_redirection(t_pipe *pptr, char ****cptr, const char *raw)
{
	int			cmds_index;
	int			number_of_commands;
	char		**data;
	char		**redir;

	pptr->num_pipes = count_char_in_str(raw, '|');
	number_of_commands = pptr->num_pipes + 1;
	if ((*cptr = malloc(sizeof(char **) * (number_of_commands + 1))) == NULL)
		return (MEM_ERROR);
	data = ft_split(raw, '|');
	redir = 0;
	cmds_index = -1;
	while (++cmds_index < number_of_commands)
	{
		(*cptr)[cmds_index] = ft_split(data[cmds_index], (char)SPACE);
		parse_redirection(&(*cptr)[cmds_index], &redir);
		redirection(redir);
		remake_redir((*cptr)[cmds_index]);
		delete_sub_in_cmd((*cptr)[cmds_index]);
		free_double_ptr((void ***)&redir);
	}
	free_double_ptr((void ***)&data);
	if (number_of_commands == cmds_index)
		(*cptr)[cmds_index] = (char **)NULL;
	return (0);
}

void
	dup2_and_close(int *fd, const int option)
{
	if (option == 0)
		dup2(fd[0], 0);
	else if (option == 1)
		dup2(fd[1], 1);
	if (option == 0 || option == 1 || option == -1)
	{
		close(fd[0]);
		close(fd[1]);
	}
}
