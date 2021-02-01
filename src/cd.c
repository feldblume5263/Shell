/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyeo <kyeo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 20:38:37 by kyeo              #+#    #+#             */
/*   Updated: 2021/02/02 05:22:22 by kyeo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void
	replace_pwd_data(t_shell *sptr, t_env *temp,\
						const char *new_dir, const char *pwd_type)
{
	temp = find_env_by_name(sptr->env, pwd_type);
	free_ptr(&(temp->data));
	temp->data = ft_strdup(new_dir);
}

void
	set_dir(char *dir)
{
	ft_memset(dir, 0, PATH_MAX);
	getcwd(dir, PATH_MAX);
}

int
	change_old_and_cur(t_shell *sptr, const char *new_dirname)
{
	t_env			*new;
	t_env			*old;

	if (*new_dirname == '-' && ft_strlen(new_dirname) == 1)
	{
		new = find_env_by_name(sptr->env, "PWD");
		old = find_env_by_name(sptr->env, "OLDPWD");
		new_dirname = ft_strdup(old->data);
		free_ptr(&(old->data));
		old->data = ft_strdup(new->data);
		free_ptr(&(new->data));
		new->data = ft_strdup(new_dirname);
		write(1, new_dirname, ft_strlen(new_dirname));
		write(1, "\n", 1);
		if (chdir(new_dirname) == -1)
			perror("mini: cd");
		free_ptr((char **)&new_dirname);
		return (1);
	}
	return (0);
}

void
	builtins_cd(t_shell *sptr, char *new_dirname)
{
	char			cur_dirname[PATH_MAX];
	t_env			*temp;

	if (change_old_and_cur(sptr, new_dirname) == 1)
		return ;
	temp = 0;
	set_dir(cur_dirname);
	replace_pwd_data(sptr, temp, cur_dirname, "OLDPWD");
	if (new_dirname == (char *)0 ||\
		(*new_dirname == '~' && ft_strlen(new_dirname) == 1))
	{
		temp = find_env_by_name(sptr->env, "HOME");
		if (chdir(temp->data) == -1)
			perror("mini: cd");
	}
	else if (chdir(new_dirname) == -1)
		perror("mini: cd");
	set_dir(cur_dirname);
	replace_pwd_data(sptr, temp, cur_dirname, "PWD");
}
