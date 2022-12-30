#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <stdlib.h>

int main(void)
{
        int     fd[2], nbytes;
        pid_t   childpid;
        char    string[] = "Hello, world!\n";
        char    readbuffer[80];

        pipe(fd);
        
        if((childpid = fork()) == -1)
        {
                perror("fork");
                exit(1);
        }

        if(childpid == 0)
        {
		/*자식 프로세스는 파이프의 입력 쪽을 닫는다*/
                close(fd[0]);

		/*파이프의 출력 쪽으로 "string"을 보낸다*/
                write(fd[1], string, strlen(string));
                exit(0);
        }
        else
        {
		/*부모 프로세스는 파이프의 출력 쪽을 닫는다*/
                close(fd[1]);

		/*파이프로 부터 문자열을 읽는다*/
                nbytes = read(fd[0], readbuffer, sizeof(readbuffer));
                printf("Received string: %s", readbuffer);
        }
        
        return(0);
}
