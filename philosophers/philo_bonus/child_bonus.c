/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuikim <yuikim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 20:13:23 by yuikim            #+#    #+#             */
/*   Updated: 2023/06/02 21:24:38 by yuikim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

int	execute_philo(t_philo *philo)
{
	philo->eat_count = 0;
	pthread_create(&(philo->thread_id), NULL, monitor_dead, philo);
	ge
}

void	*monitor_dead(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	while (1)
	{
		timestamp();
		usleep(1000);
	}
}

void	repeat(t_philo *philo)
{
	
}

int	have_forks(t_philo *philo)
{
	if (philo->philo_num == 1)
	{
		sem_wait(philo->forks);
		print(philo, "has taken a fork");
		
	}
}