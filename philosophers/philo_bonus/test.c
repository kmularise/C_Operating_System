#include "philosophers_bonus.h"
#include <string.h>

typedef struct son{
	char	*message;
	sem_t*	temp;
} son;

void *monitor_dead(void *data) {
	char *ll;
	son *son1 = (son *)data;
	while(1)
	{
		sem_wait(son1->temp);
		memcpy(ll, son1->message, 2);
		// ll = malloc(sizeof(char ) * 2);
		ll[0] = *son1->message;
		son1->message++;
		ll[1] = *son1->message;;
		printf("%s sdfsdf\n", son1->message);
		// son1->message[0] = 'b' + 10;
		usleep(2000);
		sem_post(son1->temp);
	}
	return NULL;
}

int execute_process(son *son1, int i)
{
	pthread_t thread;
	sem_unlink("sem_d");
	son1->temp = sem_open("sem_d", O_CREAT, 0644, 1);
	pthread_create(&thread, NULL, monitor_dead, son1);
	// sem_unlink("sem_d");
	// son1->temp = sem_open("sem_d", O_CREAT, 0644, 1);
	int j = 0;
	while (1)
	{
		// printf("%d", i);
		usleep(1000);
		sem_wait(son1->temp);
		son1->message[0] = 'b' + i;
		printf("%s\n", son1->message);
		sem_post(son1->temp);
		j++;
	}
	return 0;
}
int main() 
{

	pid_t pid_arr[2];

	struct timeval time;
	son son1;
	// son1.message = malloc(sizeof(char) * 2);
	// son1.message[0] = 'a';
	// son1.message[1] = 0;

	sem_unlink("sem_fork");
	son1.temp = sem_open("sem_fork", O_CREAT, 0644, 1);
	sem_wait(son1.temp);
	son1.message = malloc(sizeof(char) * 2);
	son1.message[0] = 'a';
	son1.message[1] = 0;
	sem_post(son1.temp);
	for (int i = 0; i < 2; i++)
	{
		pid_arr[i] = fork();
		if (pid_arr[i] == 0) {
			// printf("%d ");
			execute_process(&son1, i);
			break;
		}
		else {
			// printf("%s\n", son1.message);
		}
	}
	waitpid(-1, NULL, 0);
	waitpid(-1, NULL, 0);
}