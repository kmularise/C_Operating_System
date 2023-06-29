/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuikim <yuikim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 14:47:09 by yuikim            #+#    #+#             */
/*   Updated: 2023/05/28 21:10:07 by yuikim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	is_dead(t_setting *info)
{
	int	dead;

	pthread_mutex_lock(&(info->dead_mutex));
	dead = info->dead;
	pthread_mutex_unlock(&(info->dead_mutex));
	return (dead);
}

void	set_dead(t_setting *info)
{
	pthread_mutex_lock(&(info->dead_mutex));
	info->dead = 1;
	pthread_mutex_unlock(&(info->dead_mutex));
}

void	monitor_dead(t_setting *info, t_philo *philo)
{
	if (timestamp() - get_start_eat(philo) > info->time_to_die)
	{
		print(info, "is dead", philo->idx + 1);
		set_dead(info);
	}
}
