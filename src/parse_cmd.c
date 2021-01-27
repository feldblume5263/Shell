/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhpark <junhpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 22:31:32 by junhpark          #+#    #+#             */
/*   Updated: 2021/01/27 15:29:02 by kyeo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			dispence_command(t_shell *sptr, char **data)
{
	int			idx;

	idx = 0;
	if (!(data[idx]))
		return ;
	while (data[++idx])
		delete_subs(&(data[idx]));
	if (ft_strlen(data[0]) == 4 && ft_strncmp(data[0], "echo", 4) == 0)
		builtins_echo(sptr, &(data[1]));
	else if (ft_strlen(data[0]) == 3 && ft_strncmp(data[0], "env", 3) == 0)
		builtins_env(sptr->env, 0);
	else if (ft_strlen(data[0]) == 5 && ft_strncmp(data[0], "unset", 5) == 0)
		builtins_unset(sptr, &(data[1]));
	else if (ft_strlen(data[0]) == 6 && ft_strncmp(data[0], "export", 6) == 0)
		builtins_export(sptr, &(data[1]));
	else if (ft_strlen(data[0]) == 3 && ft_strncmp(data[0], "pwd", 3) == 0)
		builtins_pwd(sptr);
	else if (ft_strlen(data[0]) == 2 && ft_strncmp(data[0], "cd", 2) == 0)
		builtins_cd(sptr, data[1]);
	else
		exec(sptr, data);
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

void			parse_command(t_shell *sptr, char *raw)
{
	pid_t		pid;
	int			old_fds[2];
	int			new_fds[2];
	int			pipe_count;
	int			pipe_cmd_index;
	int			num_pipes;
	char		***data_piped;

	int			saved_stdout;
	char		**data;
	char		**redir;

	if (*raw == '\0')
		return ;
	saved_stdout = dup(STDOUT_FILENO);
	num_pipes = count_char_in_str(raw, '|');
	data_piped = malloc(sizeof(char **) * (num_pipes + 1 + 1));
	pipe_cmd_index = 0;
	data = ft_split(raw, '|');
	//printf("NUM PIPES: %d\n", num_pipes);
	while (pipe_cmd_index < (num_pipes + 1))
	{
		data_piped[pipe_cmd_index] = ft_split(data[pipe_cmd_index], (char)SPACE);
		parse_redirection(&data_piped[pipe_cmd_index], &redir);
		delete_subs(data_piped[pipe_cmd_index]);
		if (redirection(redir) < 0)
			break ;
		pipe_cmd_index += 1;
		//printf("PIPE_CMD_IONDX: %d\n", pipe_cmd_index);
	}
	free_double_ptr((void ***)&data);
	data_piped[pipe_cmd_index] = (char **)NULL;
	pipe_cmd_index = 0;
	while (data_piped[pipe_cmd_index])
	{
		// 다음으로 실행할 명령이 있다면
		if (data_piped[pipe_cmd_index + 1])
			pipe(new_fds);
		pid = fork();
		if (pid == 0)
		{
			// 이전에 호출한 명령이 있다면
			if (pipe_cmd_index)
			{
				dup2(old_fds[0], 0);
				close(old_fds[0]);
				close(old_fds[1]);
			}
			// 다음에 호출할 명령이 있다면
			if (data_piped[pipe_cmd_index + 1])
			{
				close(new_fds[0]);
				dup2(new_fds[1], 1);
				close(new_fds[1]);
			}
			dispence_command(sptr, data_piped[pipe_cmd_index]);
			return ;
		}
		else
		{
			if (pipe_cmd_index)
			{
				close(old_fds[0]);
				close(old_fds[1]);
			}
			if (data_piped[pipe_cmd_index + 1])
			{
				old_fds[0] = new_fds[0];
				old_fds[1] = new_fds[1];
			}
		}
		pipe_cmd_index += 1;
	}
	// 명령이 여러개라면
	if (pipe_cmd_index)
	{
		close(old_fds[0]);
		close(old_fds[1]);
	}
	if (num_pipes == 0)
		wait(NULL);
	else
	{
		pipe_count = 0;
		// 파이프의 개수만큼
		while (pipe_count < (num_pipes + 1))
		{
			wait(NULL);
			pipe_count += 1;
		}
	}
	free_double_ptr((void ***)&redir);
	dup2(saved_stdout, STDOUT_FILENO);
	return ;
}
