/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuikim <yuikim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 08:25:18 by yuikim            #+#    #+#             */
/*   Updated: 2023/05/29 18:06:14 by yuikim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	set_done(t_philo *philo)
{
	pthread_mutex_lock(&philo->done_mutex);
	philo->done = 1;
	pthread_mutex_unlock(&philo->done_mutex);
}

void	print(t_setting *info, char *str, int philo_idx)
{
	pthread_mutex_lock(&(info->print_mutex));
	if (!is_dead(info))
		printf("%lld %d %s\n", timestamp() - info->time_to_start,
			philo_idx, str);
	pthread_mutex_unlock(&(info->print_mutex));
}

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
		usleep(10);
	}
	return (0);
}

int	have_forks(t_setting *info, t_philo *philo)
{
	pthread_mutex_lock(&(info->forks[philo->idx].mutex));
	print(info, "has taken a fork", philo->idx + 1);
	pthread_mutex_unlock(&(info->forks[philo->idx].mutex));
	pthread_mutex_lock(&(info->forks[(philo->idx + 1)
			% (info->philo_num)].mutex));
	print(info, "has taken a fork", philo-> idx + 1);
	pthread_mutex_unlock(&(info->forks[(philo->idx + 1)
			% (info->philo_num)].mutex));
	return (eat(info, philo));
}

void	ft_usleep(int mili_second, t_philo *philo, t_setting *info)
{
	long long	time;
	long long	now;

	time = timestamp();
	now = time;
	while (now < time + (long long)mili_second)
	{
		monitor_dead(info, philo);
		usleep(10);
		now = timestamp();
	}
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
		if (philo->common_info->philo_num % 2 == 0)
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
	// philo->done = 1;
	set_done(philo);
	return (NULL);
}
