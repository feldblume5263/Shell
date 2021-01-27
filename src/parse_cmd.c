/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhpark <junhpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 22:31:32 by junhpark          #+#    #+#             */
/*   Updated: 2021/01/27 22:13:21 by kyeo             ###   ########.fr       */
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
	cmds_index = 0;
	while (cmds_index < number_of_commands)
	{
		(*cptr)[cmds_index] = ft_split(data[cmds_index], (char)SPACE);
		parse_redirection(&(*cptr)[cmds_index], &redir);
	 	free_double_ptr((void ***)&redir);
		delete_subs((*cptr)[cmds_index]);
		cmds_index += 1;
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

void
	swap_fd_value(int *old, int *new)
{
	old[0] = new[0];
	old[1] = new[1];
}

void
	wait_loop(const int max)
{
	int			count;

	count = 0;
	while (count < max)
	{
		wait(NULL);
		count += 1;
	}
}

void			sig_handler(int signo);

void			parse_command(t_shell *sptr, char *raw)
{
	pid_t		pid;
	t_pipe		pip;
	int			cmds_index;
	char		***cmds_redirected;

	if (ft_strlen(raw) == 4 && ft_strncmp("exit", raw, 4) == 0)
		builtins_exit(sptr, (char **)NULL);
	set_data_with_redirection(&pip, &cmds_redirected, raw);
	cmds_index = 0;
	while (cmds_redirected[cmds_index])
	{
		// 다음으로 실행할 명령이 있다면
		if (cmds_redirected[cmds_index + 1])
			pipe(pip.new_fds);
		pid = fork();
		if (pid == 0)
		{
			// 이전에 호출한 명령이 있다면
			if (cmds_index)
				dup2_and_close(pip.old_fds, 0);
			// 다음에 호출할 명령이 있다면
			if (cmds_redirected[cmds_index + 1])
				dup2_and_close(pip.new_fds, 1);
			dispence_command(sptr, cmds_redirected[cmds_index]);
		}
		else
		{
			if (cmds_index)
				dup2_and_close(pip.old_fds, -1);
			if (cmds_redirected[cmds_index + 1])
				swap_fd_value(pip.old_fds, pip.new_fds);
		}
		cmds_index += 1;
	}
	// 명령이 여러개라면
	if (cmds_index)
		dup2_and_close(pip.old_fds, -1);
	wait_loop(pip.num_pipes + 1);
}
