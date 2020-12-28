#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

void (*old_fun)(int);

void		sigint_handler(int signo)
{
	exit(0);
}

int			main( void)
{
	old_fun = signal(SIGINT, sigint_handler);
	while(1)
	{
		printf("문장 출력 중\n");
		sleep(1);
	}
}
