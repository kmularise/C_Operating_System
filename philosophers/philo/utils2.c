/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuikim <yuikim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 19:57:22 by yuikim            #+#    #+#             */
/*   Updated: 2023/06/01 20:07:17 by yuikim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long long	timestamp(void)
{
	long long		ms_time;
	struct timeval	standard_time;

	gettimeofday(&standard_time, NULL);
	ms_time = standard_time.tv_sec * 1000 + standard_time.tv_usec / 1000;
	return (ms_time);
}

void	print(t_setting *info, char *str, int philo_idx)
{
	pthread_mutex_lock(&(info->print_mutex));
	if (!is_dead(info))
		printf("%lld %d %s\n", timestamp() - info->time_to_start,
			philo_idx, str);
	pthread_mutex_unlock(&(info->print_mutex));
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
		usleep(1000);
		now = timestamp();
	}
}

void	execute_starvation(t_setting *info, t_philo *philo)
{
	long long	now;

	while (1)
	{
		now = timestamp();
		if (now - philo->start_eat > info->time_to_die)
		{
			print(info, "is dead", philo->idx + 1);
			set_dead(info);
			break ;
		}
		usleep(1000);
	}
}
