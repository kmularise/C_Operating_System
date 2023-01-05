#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main(void){
    pid_t pid;
    pid = fork();
    printf("my fork test");
    sleep(10); // sleep 10 sec
    exit(0);
}