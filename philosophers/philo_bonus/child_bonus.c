/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuikim <yuikim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 20:13:23 by yuikim            #+#    #+#             */
/*   Updated: 2023/06/28 11:30:54 by yuikim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

int	execute_philo(t_philo *philo)
{
	philo->eat_count = 0;
	gettimeofday(&philo->start_to_eat, NULL);
	pthread_create(&(philo->thread_id), NULL, monitor_dead, philo);
	repeat(philo);
	return (0);
}

void	*monitor_dead(void *data)
{
	t_philo		*philo;
	long long	now;
	long long	start_eat;

	philo = (t_philo *)data;
	while (1)
	{
		now = timestamp();
		sem_wait(philo->die);
		start_eat = 1000 * philo->start_to_eat.tv_sec
			+ philo->start_to_eat.tv_usec / 1000;
		if (now - start_eat > philo->time_to_die)
		{
			print(philo, "is dead");
			exit(1);
		}
		sem_post(philo->die);
		usleep(1000);
	}
}

void	eat(t_philo *philo)
{
	sem_wait(philo->die);
	gettimeofday(&philo->start_to_eat, NULL);
	sem_post(philo->die);
	print(philo, "is eating");
	ft_usleep(philo->time_to_eat);
	philo->eat_count++;
	sem_post(philo->forks);
	sem_post(philo->forks);
}

void	repeat(t_philo *philo)
{
	if (philo->idx % 2 == 1)
	{
		usleep(200);
	}
	while (1)
	{
		if (philo->eat_count == philo->num_to_eat)
			exit(0);
		if (have_forks(philo))
			break ;
		eat(philo);
		print(philo, "is sleeping");
		ft_usleep(philo->time_to_sleep);
		print(philo, "is thinking");
	}
}

int	have_forks(t_philo *philo)
{
	if (philo->philo_num == 1)
	{
		sem_wait(philo->forks);
		print(philo, "has taken a fork");
		sem_wait(philo->forks);
		return (1);
	}
	sem_wait(philo->forks);
	print(philo, "has taken a fork");
	sem_wait(philo->forks);
	print(philo, "has taken a fork");
	return (0);
}
