/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhpark <junhpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/31 21:11:47 by kyeo              #+#    #+#             */
/*   Updated: 2021/01/10 20:57:19 by junhpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define SHELL_NAME			"minishell"
# define SHELL_NAME_LENGTH	9

# define ARG_ERROR			-1
# define MEM_ERROR			-2

# include "libft.h"

/*
**	<stdio.h> for debugging
*/

# include <stdio.h>

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
**	init_env.c
*/

int					find_char_in_str(const char c, const char *str);

void				copy_until_end\
					(char **dest, const char *start, const char end);

int					make_env_node(t_env **nptr, char *env_raw_data);

int					init_env_node(t_env **nptr);

int					init_env(t_env **head, char **envp);

/*
**	env.c
*/

void				connect_new_env_node(t_env **new, t_env **eptr);

void				builtins_env(t_env *eptr, const int export_option);

/*
**	unset.c
*/

void				delete_env_node(t_env **eptr, const char *env_name);

void				builtins_unset(t_shell *sptr, char **args);

/*
**	export.c
*/

t_env				*dup_all_env(t_env *original);

void				sort_env(t_env *eptr);

t_env				*find_env_by_name(t_env *head, const char *name);

void				export_with_null_arg(t_env *original);

void				builtins_export(t_shell *sptr, char **args);

/*
**	free.c
*/

void				free_env_node(t_env *node);

void				free_all_env(t_env *env);

#endif
