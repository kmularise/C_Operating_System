/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuikim <yuikim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 11:07:51 by yuikim            #+#    #+#             */
/*   Updated: 2023/06/28 11:25:11 by yuikim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

int	initiate_setting(t_philo *setting, char **argv)
{
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
	sem_unlink("sem_die");
	philo->forks = sem_open("sem_fork", O_CREAT, 0644, philo->philo_num);
	philo->print = sem_open("sem_print", O_CREAT, 0644, 1);
	philo->die = sem_open("sem_die", O_CREAT, 0644, 1);
}

void	execute_parent(t_philo *philo, pid_t *pid_arr)
{
	int	status;
	int	i;
	int	j;

	i = -1;
	while (++i < philo->philo_num)
	{
		waitpid(-1, &status, 0);
		if (status != 0)
		{
			j = -1;
			while (++j < philo->philo_num)
			{
				kill(pid_arr[j], SIGKILL);
			}
			break ;
		}
	}
}

int	create_philos(t_philo *philo)
{
	pid_t	*pid_arr;
	int		i;

	i = -1;
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
		else
			philo->idx = -1;
	}
	if (philo->idx != -1 && pid_arr[philo->idx] == 0)
	{
		execute_philo(philo);
		return (1);
	}
	else
		execute_parent(philo, pid_arr);
	free(pid_arr);
	return (0);
}
