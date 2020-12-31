#include <stdio.h>
int			main(int argc, char **argv, char **envp)
{
	int		i;
	(void)argc;
	(void)argv;
	i = -1;
	while (envp && envp[++i])
		printf("ENV: %s\n", envp[i]);
	return (0);
}
