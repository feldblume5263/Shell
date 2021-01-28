/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyeo <kyeo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 20:38:37 by kyeo              #+#    #+#             */
/*   Updated: 2021/01/28 20:01:23 by kyeo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void
	builtins_cd(t_shell *sptr, char *new_dirname)
{
	char			cur_dirname[PATH_MAX];
	t_env			*temp;

	ft_memset(cur_dirname, 0, PATH_MAX);
	getcwd(cur_dirname, PATH_MAX);
	temp = find_env_by_name(sptr->env, "OLDPWD");
	free(temp->data);
	temp->data = ft_strdup(cur_dirname);
	if (new_dirname == (char *)0)
	{
		temp = find_env_by_name(sptr->env, "HOME");
		chdir(temp->data);
	}
	else
		chdir(new_dirname);
	temp = find_env_by_name(sptr->env, "PWD");
	free(temp->data);
	ft_memset(cur_dirname, 0, PATH_MAX);
	getcwd(cur_dirname, PATH_MAX);
	temp->data = ft_strdup(cur_dirname);
	exit(0);
}
