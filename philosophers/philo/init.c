/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuikim <yuikim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 11:07:51 by yuikim            #+#    #+#             */
/*   Updated: 2023/04/06 20:15:24 by yuikim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	initiate_setting(t_setting *setting, char **argv)
{
	pthread_mutex_init(&setting->dead_mutex, NULL);
	pthread_mutex_init(&setting->eat_mutex, NULL);
	pthread_mutex_init(&setting->print_mutex, NULL);
	pthread_mutex_init(&setting->stop_mutex, NULL);
	setting->stop_idx = 0;//필요한가?
	setting->philo_eat = 0;//ㅍㅣㄹ요한가?
	setting->philo_num = ft_atoi(argv[1]);
	setting->time_to_die = ft_atoi(argv[2]);
	setting->time_to_eat = ft_atoi(argv[3]);
	setting->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
	{
		setting->num_to_eat = ft_atoi(argv[5]);
		if (setting->num_to_eat == 0)
			return (1);
	}
	return (0);
}

int	initiate_threads(t_setting *setting)
{
	setting->
}