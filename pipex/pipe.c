#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#include <stdlib.h>

void stop(char *input)
{
	printf("%s is failed!", input);
	exit(1);
}

int main()
{
	char *arg1="-al";
	char *arg2="./";
	char *file = "/bin/ls";
	char *shell = "/bin/zsh";
	char *argv[]={file,arg1,arg2,NULL};
	int	fd[2];//read 가 첫번째 write가 두번째
	int	execve_status;
	int status;
	if (pipe(fd) == -1)//if pipe is failed, need to handle failure
		stop("pipe");
	pid_t pid = fork();
	//child process - exec 관련된 부분!
	if (pid == -1)
		stop("fork");
	if (pid == 0)
	{
		printf("child!\n");
		dup2(fd[0], 0);//표준 입력을 파이프 쓰는 쪽으로
		close(fd[1]);
		char readbuffer[30];
		int nbytes = read(fd[0],readbuffer, sizeof(readbuffer));
		return (0);
	}
	pid = waitpid(pid, &status, 0);
	if (pid < 0)
		stop("waitpid");
	dup2(fd[1], 1);
	close(fd[0]);
	execve_status = execve(file, argv, NULL);
	if (execve_status == -1)
		stop("execlp");
}