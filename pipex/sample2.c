#include <unistd.h>
#include <stdio.h>

int main(void){
        char *arg1="-al";
        char *arg2="/etc";
        char *file = "ls";
        char *argv[]={file,arg1,arg2,NULL};
        char *path = "/bin/ls";

        // printf("execl호출\n");
        // execl(path, file, arg1, arg2, NULL);

        //printf("execv호출\n");
        //execv(path, argv);

        //printf("execle호출\n");
        //execle(path, file, arg1, arg2, NULL, NULL);

        // printf("execve호출\n");
        // printf("%s", envp[0]);
        execve(path, argv, NULL);


        //printf("execlp호출\n");
        //execlp(file, file, arg1, arg2, NULL);

        //printf("execvp호출\n");
        //execvp(file,argv);

        //printf("execvpe호출\n");
        //execvpe(file,argv,NULL);


        return 0;
}