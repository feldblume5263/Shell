/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyeo <kyeo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/31 21:11:47 by kyeo              #+#    #+#             */
/*   Updated: 2021/01/03 01:03:02 by kyeo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"

typedef struct		s_env
{
	char			*name;
	char			*data;
	struct s_env	*next;
	struct s_env	*prev;
}					t_env;

typedef struct		s_shell
{
	struct s_env	*env;
}					t_shell;

/*
**	ENVIRONMENT VARIABLE PART
*/

int					make_env_node(char *env_data, t_env **node);

int					init_env(char **env, t_env **env_copy);

void				free_env_node(t_env *need_to_free);

void				connect_prev_and_next(t_env **temp);

void				free_unset_args(char **args);

int					unset(const char *arg, t_env *env_copy);

#endif
