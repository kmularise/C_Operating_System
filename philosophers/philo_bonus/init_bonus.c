/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuikim <yuikim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 11:07:51 by yuikim            #+#    #+#             */
/*   Updated: 2023/06/02 20:12:10 by yuikim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

int	initiate_setting(t_philo *setting, char **argv)
{
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
	return (0);
}

void	init_semaphores(t_philo *philo)
{
	sem_unlink("sem_fork");
	sem_unlink("sem_print");
	sem_unlink("sem_dead");
	philo->forks = sem_open("sem_fork", O_CREAT, 0644, philo->philo_num);
	philo->print = sem_open("sem_print", O_CREAT, 0644, 1);
	philo->dead = sem_open("sem_dead", O_CREAT, 0644, 1);
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

int	create_philos(t_philo *philo)
{
	pid_t	*pid_arr;
	int		i;

	i = -1;
	//ㅇㅕ기 하다 말음
	pid_arr = malloc(philo->philo_num * sizeof(pid_t));
	philo->time_to_start = timestamp();
	while (++i < philo->philo_num)
	{
		pid_arr[i] = fork();
		if (pid_arr[i] < 0)
			return (1);
		if (pid_arr[i] == 0)
		{
			philo->idx = i;
			break ;
		}
		setting->philos[i].start_eat = timestamp();
		setting->philos[i].common_info = setting;
		setting->philos[i].eat_count = 0;
		setting->philos[i].stop = 0;
		setting->philos[i].done = 0;
	}
	if (pid_arr[philo->idx] == 0)
	{
		execute_philo(philo);	
	}
	else
		execute_parent(philo, pid_arr);
	free(pid_arr);
}

int	initiate_philos(t_philo *philo)
{
	int	i;

	init_semaphores(philo);
	philo->time_to_start = timestamp();
	create_philos(philo);
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
