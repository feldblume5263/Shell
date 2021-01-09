#include "minishell.h"
#include <stdio.h>

void		free_double(char ***p)
{
	int		idx;
	int		size;

	size = 0;
	while ((*p)[size])
		size++;
	idx = 0;
	while (idx < size)
	{
		free((*p)[idx]);
		(*p)[idx] = 0;
		idx++;
	}
	free(*p);
	*p = 0;
	return ;
}

void		clear_quotes(char **cmd)
{
	int		size;
	int		count[2];
	int		start;

	count[0] = 0;
	count[1] = 0;
	size = -1;
	start = 0;
	while ((*cmd)[++size])
	{
		if ((*cmd)[size] == '"')
			count[0]++;
		else if ((*cmd)[size] == '\'')
			count[1]++;
	}
	printf("%d %d\n", count[0], count[1]);
	if (size == 0 || count[0] % 2 != 0 || count[1] % 2 != 0)
		return ;
	else
	{
		size = size - (count[0] + count[1]);
		// remove_quotes(cmd, size);
	}
}

void		parse_cmd(char **cmd)
{
	char	**pure_cmd;

	pure_cmd = ft_split(*cmd, ' ');
	clear_quotes(&pure_cmd[0]);
	free_double(&pure_cmd);
}

void		print_prompt(void)
{
	write(1, "minishell # ", 12);
}

int			cmd_join(char **cmd, char *buf, int size)
{
	int		i;
	int		j;
	char	*new;

	if (!(new = malloc(sizeof(char) * (size + 1))))
		return (-1);
	i = 0;
	while (*cmd != (char *)0 && (*cmd)[i])
	{
		new[i] = (*cmd)[i];
		i++;
	}
	j = 0;
	while (buf[j])
	{
		new[i + j] = buf[j];
		j++;
	}
	new[i + j] = '\0';
	if (*cmd != (char *)0)
		free(*cmd);
	*cmd = new;
	return (1);
}

int			make_cmd(char buf[], char **cmd)
{
	int		size;

	if (*cmd == (char *)0)
		size = ft_strlen(buf);
	else
		size = ft_strlen(*cmd) + ft_strlen(buf);
	cmd_join(cmd, buf, size);
	return (size);
}

void		getcmd(char **cmd)
{
	int		ret;
	char	buf[4096 + 1];
	int		idx;
	int		nl;

	nl = 0;
	while ((ret = read(0, buf, 4096)) > 0)
	{
		buf[ret] = '\0';
		idx = -1;
		while (buf[++idx])
		{
			if (buf[idx] == '\n')
			{
				buf[idx] = '\0';
				nl = 1;
			}
		}
		make_cmd(buf, cmd);
		if (nl == 1)
			break;
	}
}

void		prompt(char **cmd)
{
	while (1)
	{
		print_prompt();
		getcmd(cmd);
		parse_cmd(cmd);
		free(*cmd);
		*cmd = 0;
	}
}

int			main(int argc, char **argv, char **env)
{
	int			ret;
	t_shell		shell;
	char		*cmd;


	(void)argc;
	(void)argv;
	if ((ret = init_env(env, &(shell.env))) < 0)
		return (ret);
	prompt(&cmd);
	return (0);
}
