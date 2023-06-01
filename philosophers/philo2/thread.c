/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuikim <yuikim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 08:25:18 by yuikim            #+#    #+#             */
/*   Updated: 2023/06/01 20:38:05 by yuikim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	eat(t_setting *info, t_philo *philo)
{
	long long	now;

	pthread_mutex_lock(&(info->eat_mutex));
	print(info, "is eating", philo->idx + 1);
	philo->start_eat = timestamp();
	pthread_mutex_unlock(&(info->eat_mutex));
	(philo->eat_count)++;
	if (philo->eat_count == info->num_to_eat)
		return (1);
	while (1)
	{
		now = timestamp();
		if (now - philo->start_eat >= (long long)(info->time_to_eat))
			break ;
		usleep(1000);
	}
	return (0);
}

int	have_forks(t_setting *info, t_philo *philo)
{
	pthread_mutex_lock(&(info->forks[philo->idx].mutex));
	print(info, "has taken a fork", philo->idx + 1);
	pthread_mutex_unlock(&(info->forks[philo->idx].mutex));
	if (philo->idx == ((philo->idx + 1) % (info->philo_num)))
	{
		execute_starvation(info, philo);
		return (1);
	}
	pthread_mutex_lock(&(info->forks[(philo->idx + 1)
			% (info->philo_num)].mutex));
	print(info, "has taken a fork", philo-> idx + 1);
	pthread_mutex_unlock(&(info->forks[(philo->idx + 1)
			% (info->philo_num)].mutex));
	return (eat(info, philo));
}

int	execute_even_num(t_philo *philo)
{
	if (philo->idx % 2 == 0)
		if (have_forks(philo->common_info, philo))
			return (1);
	print(philo->common_info, "is sleeping", philo->idx + 1);
	ft_usleep(philo->common_info->time_to_sleep, philo, philo->common_info);
	print(philo->common_info, "is thinking", philo->idx + 1);
	if (philo->idx % 2 == 1)
		if (have_forks(philo->common_info, philo))
			return (1);
	return (0);
}

int	execute_odd_num(t_philo *philo, int philo_num)
{
	int	count;

	count = 0;
	if (philo->idx % 2 == 0 && philo->idx != philo_num - 1)
		if (have_forks(philo->common_info, philo))
			return (1);
	while (count < 2)
	{
		print(philo->common_info, "is sleeping", philo->idx + 1);
		ft_usleep(philo->common_info->time_to_sleep, philo, philo->common_info);
		print(philo->common_info, "is thinking", philo->idx + 1);
		if (count == 0 && philo->idx % 2 == 1)
			if (have_forks(philo->common_info, philo))
				return (1);
		if (count == 1 && philo->idx == philo_num - 1)
			if (have_forks(philo->common_info, philo))
				return (1);
		count++;
	}
	return (0);
}

void	*execute_philo(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	while (!is_dead(philo->common_info))
	{
		monitor_dead(philo->common_info, philo);
		if (philo->common_info->philo_num == 1)
		{
			if (have_forks(philo->common_info, philo))
				break ;
		}
		else if (philo->common_info->philo_num % 2 == 0)
		{
			if (execute_even_num(philo))
				break ;
		}
		else
		{
			if (execute_odd_num(philo, philo->common_info->philo_num))
				break ;
		}
	}
	set_done(philo);
	return (NULL);
}
