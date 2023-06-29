/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuikim <yuikim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 08:25:18 by yuikim            #+#    #+#             */
/*   Updated: 2023/06/29 18:32:18 by yuikim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	eat(t_setting *info, t_philo *philo)
{
	long long	now;

	print(info, "is eating", philo->idx + 1);
	set_start_eat(philo);
	(philo->eat_count)++;
	while (1)
	{
		now = timestamp();
		if (now - get_start_eat(philo) >= (long long)(info->time_to_eat))
			break ;
		usleep(1000);
	}
	pthread_mutex_unlock(&(info->forks[philo->idx].mutex));
	pthread_mutex_unlock(&(info->forks[(philo->idx + 1)
			% (info->philo_num)].mutex));
	pthread_mutex_lock(&(info->eat_mutex));
	pthread_mutex_unlock(&(info->eat_mutex));
	return (0);
}

int	have_forks(t_setting *info, t_philo *philo)
{
	pthread_mutex_lock(&(info->forks[philo->idx].mutex));
	print(info, "has taken a fork", philo->idx + 1);
	if (philo->idx == ((philo->idx + 1) % (info->philo_num)))
	{
		execute_starvation(info, philo);
		return (1);
	}
	pthread_mutex_lock(&(info->forks[(philo->idx + 1)
			% (info->philo_num)].mutex));
	print(info, "has taken a fork", philo-> idx + 1);
	return (eat(info, philo));
}

int	execute_routine(t_philo *philo, int philo_num)
{
	if (philo->idx % 2 == 1)
		usleep(200);
	if (philo->idx % 2 == 0 && philo_num % 2 == 1)
		usleep(400);
	have_forks(philo->common_info, philo);
	print(philo->common_info, "is sleeping", philo->idx + 1);
	ft_usleep(philo->common_info->time_to_sleep, philo, philo->common_info);
	print(philo->common_info, "is thinking", philo->idx + 1);
	return (0);
}

void	*execute_philo(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	while (!is_dead(philo->common_info))
	{
		execute_routine(philo, philo->common_info->philo_num);
		if (philo->eat_count == philo->common_info->num_to_eat)
			break ;
	}
	set_done(philo);
	return (NULL);
}
