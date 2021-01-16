/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhpark <junhpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/31 21:11:47 by kyeo              #+#    #+#             */
/*   Updated: 2021/01/16 16:36:16 by kyeo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define SHELL_NAME			"minishell"
# define SHELL_NAME_LENGTH	9

# define ARG_ERROR			-1
# define MEM_ERROR			-2

# include "libft.h"
# include <limits.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>

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
**	echo.c
*/

void				builtins_echo(t_shell *sptr, char **args, const char *input);


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
**	pwd.c
*/

void				builtins_pwd(t_shell *sptr);

/*
**	cd.c
*/

void				builtins_cd(t_shell *sptr, char *new_dirname);

/*
**	free.c
*/

void				free_env_node(t_env *node);

void				free_all_env(t_env *env);

/*
**	handle_cmd.c
*/

void				handle_quotes(char **cmd);

/*
**	getcmd.c
*/

void				prompt(t_shell *sptr, char **cmd);

void				getcmd(char **cmd);

/*
**	command.c
*/

void				command_parser(t_shell *sptr, const char *raw_data);

/*
**	exec.c
*/

void				exec(t_shell *sptr, char **args);

/*
**	utils.c
*/

void				safe_free_double(char **p);

void				safe_free(void *p);

#endif
