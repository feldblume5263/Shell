#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

typedef struct	s_env
{
	char		pwd[100];
}				t_env;


int			main(void)
{
	t_env	env;
	char	input[100];
	pid_t	child_pid;
	pid_t	wait_pid;
	int		status;

	strlcpy(env.pwd, "~/mac/os/dir/file/", 100);
	while(1)
	{
		printf("bash-3.2$ ");
		scanf("%s", input);
		if (strcmp(input, "pwd") == 0)
		{
			child_pid = fork();
			if (child_pid < 0)
			{
				printf("fork Error\n");
				exit(0);
			}
			else if (child_pid == 0)
			{
				printf("%s\n", env.pwd);
				sleep(1);
				exit(3);
			}
			else
			{
				wait_pid = wait(&status);
			}
		}
	}
}
