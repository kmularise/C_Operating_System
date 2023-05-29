/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuikim <yuikim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 11:07:51 by yuikim            #+#    #+#             */
/*   Updated: 2023/05/29 18:01:32 by yuikim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	initiate_setting(t_setting *setting, char **argv)
{
	pthread_mutex_init(&setting->dead_mutex, NULL);
	pthread_mutex_init(&setting->eat_mutex, NULL);
	pthread_mutex_init(&setting->print_mutex, NULL);
	pthread_mutex_init(&setting->stop_mutex, NULL);
	pthread_mutex_init(&setting->total_eat_mutex, NULL);
	pthread_mutex_init(&setting->eat_all_mutex, NULL);
	setting->dead = 0;
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
	else
		setting->num_to_eat = -1;
	setting->philos = malloc(sizeof(t_philo) * (setting->philo_num));
	return (0);
}

static void	initiate_forks(t_setting *setting)
{
	int	i;

	i = -1;
	setting->forks = malloc(sizeof(t_philo) * (setting->philo_num));
	while (++i < setting->philo_num)
	{
		setting->forks[i].state = AVAILABLE;
		pthread_mutex_init(&(setting->forks[i].mutex), NULL);
	}
}

static void stop_philos(t_setting *setting) 
{
	int	i;

	i = -1;
	while (++i < setting->philo_num)
	{
		pthread_mutex_lock(&(setting->stop_mutex));
		setting->philos[i].stop = 1;
		pthread_mutex_unlock(&(setting->stop_mutex));
	}
}

int	is_all_philos_done(t_setting *setting)
{
	int	i;
	int	result;
	int	done;

	result = 1;
	i = -1;
	while (++i < setting->philo_num)
	{
		pthread_mutex_lock(&setting->philos[i].done_mutex);
		done = setting->philos[i].done;
		pthread_mutex_unlock(&setting->philos[i].done_mutex);
		if (!done)
		{
			result = 0;
			break ;
		}
	}
	return (result);
}

int	initiate_philos(t_setting *setting)
{
	int	i;

	initiate_forks(setting);
	setting->time_to_start = timestamp();
	i = -1;
	while (++i < setting->philo_num)
	{
		setting->philos[i].idx = i;
		setting->philos[i].start_eat = timestamp();
		setting->philos[i].common_info = setting;
		setting->philos[i].eat_count = 0;
		setting->philos[i].stop = 0;
		setting->philos[i].done = 0;
		pthread_mutex_init(&setting->philos[i].done_mutex, NULL);
		if (pthread_create(&setting->philos[i].thread_id, NULL,
				execute_philo, &setting->philos[i]) != 0)
			return (1);
	}
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
	return (0);
}
