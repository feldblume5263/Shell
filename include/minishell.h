/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyeo <kyeo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/31 21:11:47 by kyeo              #+#    #+#             */
/*   Updated: 2021/01/01 00:32:05 by kyeo             ###   ########.fr       */
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

int					make_env_node(char *env_data, t_env **node);

int					init_env(char **env, t_env **env_copy);

#endif
