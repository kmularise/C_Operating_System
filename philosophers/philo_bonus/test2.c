#include "philosophers_bonus.h"
#include <string.h>
#include <stdlib.h>

typedef struct son {
    char* message;
    sem_t* temp;
} son;

void* monitor_dead(void* data) {
    son* son1 = (son*)data;
    char* ll = malloc(sizeof(char) * 2);  // Allocate memory for ll
    while (1) {
        sem_wait(son1->temp);
        memcpy(ll, son1->message, 2);
        ll[0] = son1->message[0];  // Update the value of ll[0]
        son1->message++;  // Increment the pointer to access the next character
        ll[1] = son1->message[0];
        printf("%s sdfsdf\n", ll);
        usleep(2000);
        sem_post(son1->temp);
    }
    free(ll);  // Free the allocated memory
    return NULL;
}

int execute_process(son* son1, int i) {
    pthread_t thread;
    sem_unlink("sem_d");
    son1->temp = sem_open("sem_d", O_CREAT, 0644, 1);
    pthread_create(&thread, NULL, monitor_dead, son1);

    int j = 0;
    while (1) {
        usleep(1000);
        sem_wait(son1->temp);
        son1->message[0] = 'b' + i;
        printf("%s\n", son1->message);
        sem_post(son1->temp);
        j++;
    }
    return 0;
}

int main() {
    pid_t pid_arr[2];

    son son1;
    son1.message = malloc(sizeof(char) * 2);
    son1.message[0] = 'a';
    son1.message[1] = 0;

    sem_unlink("sem_fork");
    son1.temp = sem_open("sem_fork", O_CREAT, 0644, 1);
    // sem_wait(son1.temp);
    // sem_post(son1.temp);

    for (int i = 0; i < 2; i++) {
        pid_arr[i] = fork();
        if (pid_arr[i] == 0) {
            execute_process(&son1, i);
            break;
        }
    }

    waitpid(-1, NULL, 0);
    waitpid(-1, NULL, 0);

    // Clean up and close the semaphore
    sem_close(son1.temp);
    sem_unlink("sem_d");

    free(son1.message);

    return 0;
}