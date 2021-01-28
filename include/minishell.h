/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhpark <junhpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/31 21:11:47 by kyeo              #+#    #+#             */
/*   Updated: 2021/01/28 15:11:30 by junhpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define SHELL_NAME			"minishell"
# define SHELL_NAME_LENGTH	9

# define ARG_ERROR			-1
# define MEM_ERROR			-2

# define BIG_Q				128
# define LIT_Q				129
# define SPACE				130
# define DIV				131
# define ENV				132

# include "libft.h"
# include <limits.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <errno.h>

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


typedef struct		s_redir
{
	char			**in;
	char			**out_s;
	char			**out_d;
}					t_redir;


/*
**	prompt.c
*/

void				prompt(t_shell *sptr);

void				print_prompt();

int					divide_cmds(char ***cmds, char **cmd);

int					find_system_error(char **cmds);

int					find_system_dup(char **data);


/*
**	refine_cmd.c
*/

void				refine_cmd(char **cmd);

void				distinguish_spaces(char **cmd);

void				distinguish_quotes(char **cmd);

void				distinguish_semicolon(char **cmd);

/*
**	get_cmd.c
*/

void				getcmd(char **cmd);

int					make_cmd(char buf[], char **cmd);

int					cmd_join(char **cmd, char *buf, int size);


/*
**	parse_cmd.c
*/

void				parse_command(t_shell *sptr, char *raw);

void				dispence_command(t_shell *sptr, char **data);

void				free_double(char ***dptr);


/*
**	parse_utils.c
*/

int					is_closed(char *str, int idx);

void				delete_subs(char **cmd);

void				remove_backslash(char **cmd);

void				remove_quotes(char **cmd);

void				get_env_sign(char **cmd);

/*
**	redirection.c
*/

int					redirection(char **redir);

int					handle_redir_error(char **redir);

int					redirect_out(char *redir);

int					redirect_out_d(char *redir);

int					redirect_in(char *redir);

/*
**	parse_redirection.c
*/

int					parse_redirection(char ***data, char ***redir);

void				ch_without_redir(char ***data, char ***res, char ***redir);

void				get_redir(char *red, char ***res);

int					find_redir(char *chunk);


/*
**	redirection_utils.c
*/

void				init_redir(char ***redir, int size);

int					count_all(char **data);

int					count_ch(char **data);

/*
**	echo.c
*/

void				builtins_echo(t_shell *sptr, char **data);

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
**	exec.c
*/

void				exec(t_shell *sptr, char **args);

#endif
