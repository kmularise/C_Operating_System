#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/wait.h>

int main(int argc, char **argv)
{
	pid_t pid;
	int status;
	printf("start!\n");

	pid = fork();
	if (pid == 0){
		char *line ="eui";
		printf("%s child process!\n", line);
		sleep(4);
		// printf("1");
		// sleep(4);
		return (0);
	}
	pid = waitpid(pid, &status, 0);
	printf("s child process!\n");

	sleep(4);
	return (0);
}