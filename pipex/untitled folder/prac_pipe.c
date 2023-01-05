#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/wait.h>

#define MAX_BUF_SIZE 256

int main(void){
    char    buf[MAX_BUF_SIZE];
    pid_t   pid;
    int     status;

    fprintf(stdout, "%% ");
    if(fgets(buf, MAX_BUF_SIZE, stdin) != NULL){
        if(buf[strlen(buf) - 1] == '\n')
            buf[strlen(buf) - 1] = 0;

        if((pid = fork()) < 0){
            fprintf(stderr,"fork error");
        }
        else if(pid == 0){ // 자식의 경우
            execlp(buf, buf, (char *)0);
            fprintf(stderr,"couldn't execute: %s", buf);
            exit(1);
        }
		// 부모의 경우
        if((pid = waitpid(pid, &status, 0)) < 0)
            fprintf(stderr, "waitpid error");
        fprintf(stdout, "%% ");
    }
    exit(0);
}