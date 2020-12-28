#include <stdio.h>
#include <unistd.h>

#ifndef _MAX_PATH
#define _MAX_PATH 260
#endif

int main(void)
{
	char strBuffer[_MAX_PATH] = {0, };
	char strChangeDir[_MAX_PATH] = {"/Users/Feldblume/Documents/Shell/"};
	char buf[255];
	getcwd(buf, 255);
	printf("현재위치: %s\n", buf);

	int nResult = chdir(strChangeDir);

	if(nResult == 0)
	{
		printf("이동 성공\n");
	}
	else if( nResult == -1 )
	{
		perror("cd");
	}
	getcwd(buf, 255);
	printf("이동후위치: %s\n", buf);
	return 0;
}
