/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhpark <junhpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/27 14:06:55 by junhpark          #+#    #+#             */
/*   Updated: 2020/12/27 23:26:40 by junhpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int main()
{
    pid_t pid;
    int status;

    pid = fork();
    // 자식 프로세스
    if (pid < 0)
    {
        perror("FORK ERROR :");
        exit(0);
    }

    if (pid == 0)
    {
        int i;
        for (i = 0; i < 5; i++)
        {
            printf("Child : %d\n", i);
			printf("%d\n", getppid());
			printf("%d\n", getpid());
            sleep(2); // 프로그램을 잠깐 지연시키는(재우는) 함수
        }
        exit(3);
    }
    else
    {
        // 부모프로세스는 자식프로세스가
        // 종료할때까지 기다린다.
        printf("I wait Child(%d)\n", pid);
        wait(&status);
        printf("Child is exit (%d)\n", status);
    }
}
