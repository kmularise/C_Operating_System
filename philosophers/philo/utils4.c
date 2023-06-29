#include "philosophers.h"

long long	get_start_eat(t_philo *philo)
{
	long long	start_eat;

	pthread_mutex_lock(&philo->start_eat_mutex);
	start_eat = philo->start_eat;
	pthread_mutex_unlock(&philo->start_eat_mutex);
	return (start_eat);
}

void	set_start_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->start_eat_mutex);
	philo->start_eat = timestamp();
	pthread_mutex_unlock(&philo->start_eat_mutex);
}

int	get_done(t_philo *philo)
{
	int	done;

	pthread_mutex_lock(&philo->done_mutex);
	done = philo->done;
	pthread_mutex_unlock(&philo->done_mutex);
	return (done);
}
