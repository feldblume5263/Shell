/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyeo <kyeo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 20:20:48 by kyeo              #+#    #+#             */
/*   Updated: 2021/01/10 00:48:19 by kyeo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env
	*dup_all_env(t_env *original)
{
	t_env			*org_head;
	t_env			*dup_head;
	t_env			*dup_temp;
	t_env			*duplicate;

	org_head = original;
	init_env_node(&duplicate);
	dup_head = duplicate;
	duplicate->name = ft_strdup(original->name);
	duplicate->data = ft_strdup(original->data);
	original = original->next;
	while (original)
	{
		dup_temp = duplicate;
		init_env_node(&duplicate);
		duplicate->name = ft_strdup(original->name);
		duplicate->data = ft_strdup(original->data);
		dup_temp->next = duplicate;
		duplicate->prev = dup_temp;
		original = original->next;
	}
	original = org_head;
	return (dup_head);
}

void
	sort_env(t_env *eptr)
{
	t_env			temp;
	t_env			*head;
	t_env			*cmp;

	head = eptr;
	while (eptr->next)
	{
		cmp = eptr->next;
		while (cmp)
		{
			if (ft_strncmp(eptr->name, cmp->name, ft_strlen(cmp->name)) > 0)
			{
				temp.name = eptr->name;
				temp.data = eptr->data;
				eptr->name = cmp->name;
				eptr->data = cmp->data;
				cmp->name = temp.name;
				cmp->data = temp.data;
			}
			cmp = cmp->next;
		}
		eptr = eptr->next;
	}
	env(head);
}

void
	export(t_shell *sptr, char **args)
{
	t_env			*dup_env;

	dup_env = dup_all_env(sptr->env);
	sort_env(dup_env);
	(void)args;
}

void
	command_parser(t_shell *sptr, const char *input)
{
	int				data_index;
	char			**data;

	data = ft_split(input, ' ');
	if (ft_strncmp(data[0], "env", 3) == 0)
	{
	}
	else if (ft_strncmp(data[0], "unset", 5) == 0)
	{
		unset(sptr, &(data[1]));
	}
	else if (ft_strncmp(data[0], "export", 6) == 0)
	{
		export(sptr, &(data[1]));
	}
	data_index = 0;
	while (data[data_index])
	{
		free(data[data_index]);
		data_index += 1;
	}
	free(data);
}

int
	main(int argc, char **argv, char **envp)
{
	int				ret;
	t_shell			shell;

	if (argc != 1 || (ft_strncmp(argv[0], "./a.out", 7) != 0))
	{
		// error handling - invalid arg
		printf("ERROR OCCURED - ARGC MUST BE 1\n");
	}
	if ((ret = init_env(&(shell.env), envp)) < 0)
	{
		// error handling - must free node data
		printf("ERROR OCCURED - INIT ENV FAILED\n");
	}
	env(shell.env);
	printf("======================\n\n");
	printf("======================\n\n");
	command_parser(&shell, "unset WATER FIRE");
	env(shell.env);
	printf("======================\n\n");
	export(&shell, (char **)0);
	printf("======================\n\n");
	env(shell.env);
	return (0);
}
