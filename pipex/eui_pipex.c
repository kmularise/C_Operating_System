#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BUFF_SIZE 1024

void show_error(char *error_message)
{
	perror(error_message);
	exit(1);
}

int  main()
{
	int	pipes[2];
	char buff[BUFF_SIZE];
	pid_t pid;
	int status;

	if (pipe(pipes) == -1)
		show_error("파이프 생성 실패");
	pid = fork();
	if (pid == -1)
		show_error("자식 프로세스 생성 실패");
	else if (pid == 0)
	{	
		sleep(1);
		sprintf(buff, "check 일방향 통신\n");
		write(pipes[1], buff, strlen(buff));
		printf("자식 프로세스!\n");
	}
	else
	{
		pid = waitpid(0, &status,0);
		printf("부모 %d",status);
		if (pid == -1)
			show_error("부모 프로세스 대기 실패");
		read(pipes[0], buff, BUFF_SIZE);
		printf("제대로 나오는지? %s", buff);
	}

}