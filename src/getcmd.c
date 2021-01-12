#include "minishell.h"
#include <stdio.h>

void		safe_free_double(char ***p)
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
		handle_quotes(cmd);
		write(1, *cmd, ft_strlen(*cmd));
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
	prompt(&cmd);
	return (0);
}

