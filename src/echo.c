/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhpark <junhpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 21:20:10 by junhpark          #+#    #+#             */
/*   Updated: 2021/01/14 00:58:58 by junhpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			echo_env(t_shell *sptr, char *env)
{
	t_env	*temp;

	if ((temp = find_env_by_name(sptr->env, &(env[1]))) == (t_env *)0)
		return ;
	write(1, temp->data, ft_strlen(temp->data));
}

void			get_env_sign(t_shell *sptr, char *input)
{
	int			idx;
	char		**env;

	idx = 0;
	while (input[idx])
	{
		if (input[idx] == '$')
		{
			env = ft_split(&(input[idx]), ' ');
			echo_env(sptr, env[0]);
			while (input[idx] && input[idx] != ' ')
				idx++;
		}
		write(1, &(input[idx]), 1);
		if (input[idx])
			idx++;
	}
	safe_free_double(env);
}

void			echo_with_option(t_shell *sptr, const char *input)
{
	int			idx;
	int			nl_idx;
	char		*input_cp;

	input_cp = ft_strdup(input);
	idx = 4;
	while (input_cp[idx] == ' ')
		idx++;
	idx += 2;
	while (input_cp[idx] == ' ')
		idx++;
	nl_idx = 0;
	while (input_cp[nl_idx])
		nl_idx++;
	input_cp[--nl_idx] = '\0';
	get_env_sign(sptr, &(input_cp[idx]));
	free(input_cp);
}

void			echo_without_option(t_shell *sptr, const char *input)
{
	int			idx;

	(void)sptr;

	idx = 4;
	while (input[idx] == ' ')
		idx++;
	get_env_sign(sptr, (char *)&(input[idx]));
}

void			builtins_echo(t_shell *sptr, char **args, const char *input)
{
	char		**div_arg;

	div_arg = ft_split(*args, ' ');
	(void)sptr;
	if (ft_strncmp(div_arg[0], "-n", 2) == 0 && ft_strlen(div_arg[0]) == 2)
		echo_with_option(sptr, input);
	else
		echo_without_option(sptr, input);
}
