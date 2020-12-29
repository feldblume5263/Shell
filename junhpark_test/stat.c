#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <fcntl.h>

#define BUF_SIZE 1000

void error_handling(char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}

int main(int argc, char *argv[])
{
	int org_fd, cp_fd;
	char buf[BUF_SIZE];
	struct stat in_file_stat;
	int file_permission = 0;
	int read_size = 0;
	int count = 0;

	if (argc != 3)
	{
		printf("Usage : %s <origin file> <copy file>\n", argv[0]);
		exit(1);
	}

	stat(argv[1], &in_file_stat);

	file_permission = in_file_stat.st_mode;

	org_fd = open(argv[1], O_CREAT | O_RDONLY, 0777);
	cp_fd = open(argv[2], O_CREAT | O_WRONLY, file_permission);

	if (org_fd == -1 || cp_fd == -1)
		error_handling("open() error!");

	while (1)
	{
		read_size = read(org_fd, buf, BUF_SIZE);

		if (read_size == -1)
		{
			error_handling("read() error!");
		}
		else if (read_size < BUF_SIZE)
		{
			puts(buf);
			++count;
			write(cp_fd, buf, read_size);
			printf("EOF\n");
			break;
		}
		puts(buf);
		++count;
		write(cp_fd, buf, BUF_SIZE);
	}

	printf("read&write call : %d\n", count);

	close(org_fd);
	close(cp_fd);

	return 0;
}
