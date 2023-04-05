#include <pthread.h>
#include <stdio.h>

pthread_mutex_t count_mutex;
long long count;

void	increment_count(long long *count, pthread_mutex_t *count_mutex)
{
	pthread_mutex_lock(count_mutex);
	*count = *count + 1;
	pthread_mutex_unlock(count_mutex);
}

long long	get_count(long long *count, pthread_mutex_t *count_mutex)
{
	long long	c;

	pthread_mutex_lock(&count_mutex);
	c = *count;
	pthread_mutex_unlock(&count_mutex);
	return (c);
}

int main()
{
	pthread_mutex_t	count_mutex;
	long long 		count;

	count = 0;
	int i = 0;
	while(i < 100)
	{
		increment_count();
		get_count();
		printf("%lld\n",count);
		i++;
	}
}