#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include "philosophers.h"

// 쓰레드 함수
void *test(void *data)
{
	long long i;
	i = 100;
	printf("%lld\n", i);
	return (void *)(i);
}

void	*increment_count(long long *count, pthread_mutex_t *count_mutex)
{
	pthread_mutex_lock(count_mutex);
	*count = *count + 1;
	pthread_mutex_unlock(count_mutex);
	return ((void *)count);
}

long long	get_count(long long *count, pthread_mutex_t *count_mutex)
{
	long long	c;

	pthread_mutex_lock(count_mutex);
	c = *count;
	pthread_mutex_unlock(count_mutex);
	return (c);
}

void	*test2(void *input)
{
	t_phillo *temp;
	temp = (t_phillo *)input;
	return increment_count(temp->count, temp->count_mutex);
}


int main()
{
	long long a = -100;
	pthread_t thread_t;
	long long status;
	pthread_mutex_t	count_mutex;
	long long 		count;
	count = 0;
	for (int j = 0; j < 3; j++)
	{
	// 쓰레드를 생성한다. 
		if (pthread_create(&thread_t, NULL, increment_count, (void *)&a) < 0)
		{
			perror("thread create error:");
			exit(0);
		}
		pthread_join(thread_t, (void **)&status);
		// 쓰레드가 종료되기를 기다린후 
		// 쓰레드의 리턴값을 출력한다. 
		// pthread_join(thread_t, (void **)&status);
		printf("Thread End %lld\n", status);
	}
	return 1;
}
		