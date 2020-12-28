#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/resource.h>


void ViewRUsage(pid_t pid, struct rusage *pru);
int main()
{
    pid_t pid = fork();

    if(pid == -1)
    {
        perror("error fork");
        return 0;
    }

    if(pid>0)
    {
        printf("<parent> fork child pid:%u\n",pid);
        int rvalue = 0;
        struct rusage ru;
        pid_t wpid = wait3(&rvalue,0, &ru);
        ViewRUsage(wpid, &ru);
    }
    else
    {
        printf("<child> pid:%d \n",getpid());
        int i = 0;
		int j;
		while (i < 100000)
        {
			j = 0;
			while (j < 100000)
			{
				j++;
			}
			i++;
        }
    }
    return 0;
}
void ViewRUsage(pid_t pid, struct rusage *pru)
{
    printf("\n=== pid rusage info ===\n");
    struct timeval *tv = &(pru->ru_utime);
    printf("user CPU time used [%ld]sec [%d]usec\n", tv->tv_sec,tv->tv_usec );
    tv = &(pru->ru_stime);
    printf("system CPU time used [%ld]sec [%d]usec\n", tv->tv_sec,tv->tv_usec );
}
