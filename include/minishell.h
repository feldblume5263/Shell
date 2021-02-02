/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhpark <junhpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/31 21:11:47 by kyeo              #+#    #+#             */
/*   Updated: 2021/02/02 15:28:14 by kyeo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define SHELL_NAME				"minishell"
# define SHELL_NAME_LENGTH		9

# define ARG_ERROR				-1
# define MEM_ERROR				-2

# define BIG_Q					128
# define LIT_Q					129
# define SPACE					130
# define DIV					131
# define ENV					132
# define RDROUT					133
# define RDRIN					134
# define PIPE					135
# define BSLASH					136

# define CMD_NOT_FOUND			"command not found\n"
# define CMD_NOT_FOUND_SIZE		18
# define NO_FILE_OR_DIR			"No such file or directory\n"
# define NO_FILE_OR_DIR_SIZE	27

# include "libft.h"
# include <limits.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <errno.h>
# include <signal.h>

/*
**	<stdio.h> for debugging
*/

# include <stdio.h>

typedef struct		s_pipe
{
	int				num_pipes;
	int				new_fds[2];
	int				old_fds[2];
}					t_pipe;

typedef struct		s_cmd
{
	int				builtins;
	int				cmds_index;
	pid_t			pid;
	char			***cmds_redirected;
	t_pipe			pip;
}					t_cmd;

typedef struct		s_redir
{
	char			**in;
	char			**out_s;
	char			**out_d;
}					t_redir;

typedef struct		s_env
{
	char			*name;
	char			*data;
	struct s_env	*next;
	struct s_env	*prev;
}					t_env;

typedef struct		s_path
{
	int				index;
	char			*command;
	char			*absolute;
	char			**data;
	t_env			*env;
}					t_path;

typedef struct		s_shell
{
	char			***envp;
	struct s_env	*env;
	int				saved_stdout;
	int				saved_stdin;
	int				exit_code;
}					t_shell;

int					g_status;

/*
**	prompt.c
*/

void				prompt(t_shell *sptr);

void				prepare_std(t_shell *sptr);

void				print_prompt();

void				divide_cmds(char ***cmds, char **cmd);

void				sig_handler(int signo);

/*
**	start_end.c
*/

void				finish_cycle(char ***cmds, char **cmd, t_shell *sptr);

void				restore_std(t_shell *sptr);

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

void				dispence_command(t_shell *sptr,\
										char **data,\
										const int builtins);

/*
**	parse_utils.c
*/

int					is_closed(char *str, int idx);

void				delete_subs(char **cmd);

void				remove_backslash(char **cmd);

void				remove_quotes(char **cmd);

void				get_env_sign(char **cmd);

/*
**	prepare_line.c
*/

void				insert_appro_space(char **cmd);

void				reload_line(char *cmd, char **res);

void				put_redirdouble(char *cmd, char **res,\
									int *idx, int *res_idx);

void				put_others(char *cmd, char **res, int *idx, int *res_idx);

int					count_add_space(char *cmd);

/*
**	handle_error.c
*/

int					handle_cmd_error(char *cmd);

int					find_system_error(char **cmds);

int					find_system_dup(char **data);

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

void				change_redir(char **cmd);

/*
**	redirection_utils.c
*/

void				remake_redir(char **cmds);

void				init_redir(char ***redir, int size);

int					count_all(char **data);

int					count_ch(char **data);

/*
**	echo.c
*/

void				builtins_echo(t_shell *sptr, char **data);

void				print_with_opt(t_shell *sptr, char **data);

void				print_without_opt(t_shell *sptr, char **data);

void				print_env(t_shell *sptr, char *env);
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

int					is_env_closed(char *str, int idx);

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

void				replace_pwd_data(t_shell *sptr,\
										t_env *temp,\
										const char *new_dir,\
										const char *pwd_type);

void				set_dir(char *dir);

int					change_old_and_cur(t_shell *sptr, const char *new_dirname);

void				builtins_cd(t_shell *sptr, char *new_dirname);

/*
**	exit.c
*/

void				builtins_exit(t_shell *sptr, char **args);

/*
**	free.c
*/

void				free_env_node(t_env *node);

void				free_all_env(t_env *env);

void				free_double_ptr(void ***dptr);

void				free_ptr(char **ptr);

void				free_path_data(t_path *path_ptr, const int option);

/*
**	path_utils.c
*/

int					is_path(const char *command);

int					is_executable_file(const char *command);

void				free_and_change_to_dup(char **args,\
											const int arg_index,\
											const char *new);

/*
**	path.c
*/

void				init_path_data(t_path *path_ptr);

void				set_absolute_path(t_path *path_ptr, char **args);

void				path_join(t_shell *sptr, char **args);

/*
**	exec.c
*/

void				print_command_error(const char *cmd, const int type);

void				execute_binary(t_shell *sptr, char **args);

void				exec(t_shell *sptr, char **args);

/*
**	pipe_utils.c
*/

void				swap_fd_value(int *old, int *new);

void				wait_loop(const int max);

void				pipe_child(t_cmd *cptr);

void				pipe_parent(t_shell *sptr, t_cmd *cptr);

void				pipe_end(t_cmd *cptr, t_pipe *pptr, const int cmds_index);

/*
**	set_cmd_data.c
*/

int					is_builtins(char **data);

int					count_char_in_str(const char *string, const char c);

int					set_data_with_redirection(t_pipe *pptr,\
												char ****cptr,\
												const char *raw);

void				dup2_and_close(int *fd, const int option);

/*
**	signal.c
*/

void				child_sig_handler(int signo);

void				sig_handler(int signo);

void				sig_init(void);

#endif
