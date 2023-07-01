/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuikim <yuikim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 17:23:41 by yuikim            #+#    #+#             */
/*   Updated: 2023/07/01 17:23:51 by yuikim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	create_monitor_dead(t_setting *setting)
{
	pthread_create(&setting->watch_thread_id, NULL,
		execute_monitor_dead, setting);
}

int	initiate_philos(t_setting *setting)
{
	int	i;

	initiate_forks(setting);
	setting->time_to_start = timestamp();
	create_philos(setting);
	create_monitor_dead(setting);
	while (1)
	{
		if (is_all_philos_done(setting))
			break ;
		if (is_dead(setting))
			break ;
	}
	i = -1;
	while (++i < setting->philo_num)
	{
		if (pthread_join(setting->philos[i].thread_id, NULL) != 0)
			return (1);
	}
	if (pthread_join(setting->watch_thread_id, NULL) != 0)
		return (1);
	return (0);
}
