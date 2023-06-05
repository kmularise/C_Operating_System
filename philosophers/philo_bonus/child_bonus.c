/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuikim <yuikim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 20:13:23 by yuikim            #+#    #+#             */
/*   Updated: 2023/06/05 19:28:48 by yuikim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

int	execute_philo(t_philo *philo)
{
	philo->eat_count = 0;
	philo->time_to_start = timestamp();
	philo->time_to_eat = timestamp();
	pthread_create(&(philo->thread_id), NULL, monitor_dead, philo);
	repeat(philo);
	return (0);
}

void	*monitor_dead(void *data)
{
	t_philo	*philo;
	long	now;

	philo = (t_philo *)data;
	while (1)
	{
		now = timestamp();
		sem_wait(philo->die);
		if (now - philo->last_eat > philo->time_to_die) {
			print(philo, "is dead");
			exit(1);
		}
		sem_post(philo->die);
		usleep(1000);
	}
}

void	eat(t_philo *philo)
{
	print(philo, "is eating");
	philo->last_eat = timestamp();
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
		if (have_forks(philo))
			break ;
		if (philo->eat_count == philo->num_to_eat)
			exit(0);
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
	sem_swait(philo->forks);
	print(philo, "has taken a fork");
	return (0);
}