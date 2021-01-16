/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhpark <junhpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 21:20:10 by junhpark          #+#    #+#             */
/*   Updated: 2021/01/16 21:27:42 by junhpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

int				is_dollar(char *ch, int idx)
{
	if (ch[idx + 1] && (ch[idx + 1] == ' ' || ch[idx + 1] == '\n'))
		return (1);
	else if (!(ch[idx + 1]))
		return (1);
	else
		return (0);
}

int				print_spec()
{
	return (1);
}

int				is_spec(char *ch, int idx)
{
	if (ch[idx + 1])
	{
		if (ch[idx + 1] == '0')
			write(1, "bash", 4);
		else if (ch[idx + 1] == '*')
		{

		}
		else if (ch[idx + 1] == '#')
		{

		}
		else if (ch[idx + 1] == '$')
		{

		}
		return (1);
	}
	else
		return (0);
}

int				find_fake_quotes(char *ch)
{
	if (*ch == '\\' && ch + 1 && (*(ch + 1) == '"' || *(ch + 1) == '\''))
		return (1);
	else
		return (0);
}

void			echo_env(t_shell *sptr, char *env)
{
	t_env	*temp;
	int		tag;

	tag = 0;
	if (env[ft_strlen(env) - 1] == '\n')
	{
		env[ft_strlen(env) - 1] = '\0';
		tag = 1;
	}
	if ((temp = find_env_by_name(sptr->env, &(env[1]))) == (t_env *)0)
		return ;
	write(1, temp->data, ft_strlen(temp->data));
	if (tag == 1)
		write(1, "\n", 1);
}

void			get_env_sign(t_shell *sptr, char *input)
{
	int			idx;
	char		**env;
	int			spec_tag;

	idx = 0;
	spec_tag = 0;
	while (input[idx])
	{
		if (input[idx] && input[idx] == '$')
		{
			if (!(is_dollar(input, idx)) && !(spec_tag = is_spec(input, idx)))
			{
				env = ft_split(&(input[idx]), ' ');
				echo_env(sptr, env[0]);
				safe_free_double(env);
				while (input[idx] && input[idx] != ' ')
					idx++;
			}
		}
		if (spec_tag)
			idx += 2;
		write(1, &(input[idx]), 1);
		if (input[idx])
			idx++;
	}
}

void			echo_with_option(t_shell *sptr, const char *input)
{
	int			idx;
	int			nl_idx;
	char		*input_cp;

	input_cp = ft_strdup(input);
	idx = 0;
	while (input_cp[idx] && input_cp[idx] == ' ')
		idx++;
	idx += 4;
	while (input_cp[idx] && input_cp[idx] == ' ')
		idx++;
	idx += 2;
	while (input_cp[idx] && input_cp[idx] == ' ')
		idx++;
	nl_idx = 0;
	while (input_cp[nl_idx])
		nl_idx++;
	input_cp[--nl_idx] = '\0';
	get_env_sign(sptr, &(input_cp[idx]));
	safe_free(input_cp);
}

void			echo_without_option(t_shell *sptr, const char *input)
{
	int			idx;

	idx = 0;
	while (input[idx] && input[idx] == ' ')
		idx++;
	idx += 4;
	while (input[idx] && input[idx] == ' ')
		idx++;
	get_env_sign(sptr, (char *)&(input[idx]));
}

void			builtins_echo(t_shell *sptr, char **args, const char *input)
{
	char		**div_arg;

	if (!(*args))
	{
		write(1, "\n", 1);
		return ;
	}
	div_arg = ft_split(*args, ' ');
	if (ft_strncmp(div_arg[0], "-n", 2) == 0 && (ft_strlen(div_arg[0]) == 2 ||
		(ft_strlen(div_arg[0]) == 3 && div_arg[0][2] == '\n')))
	{
		echo_with_option(sptr, input);
	}
	else if (*args)
		echo_without_option(sptr, input);
	return ;
}
