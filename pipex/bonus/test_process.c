#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
    int pid = fork();
    int pid2 = fork();
    int stat;
    int stat2;
    if (pid == 0)
    {
        sleep(1);
        printf("child end\n");
        return 0;
    }
    if (pid2 == 0)
    {
        sleep(7);
        printf("child2 end\n");
    }
    while (waitpid(pid, &stat, WNOHANG) == 0 || waitpid(pid2, &stat, WNOHANG) == 0)
    {
        printf("not %d\n", waitpid(pid, &stat, WNOHANG));
        printf("not %d\n", waitpid(pid2, &stat2, WNOHANG));
    }
    printf("end %d\n", waitpid(pid, &stat, WNOHANG));
}