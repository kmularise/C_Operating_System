/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuikim <yuikim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 08:25:18 by yuikim            #+#    #+#             */
/*   Updated: 2023/04/07 11:31:56 by yuikim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"



void	print(t_setting *info, char *str, int philo_idx)
{
	pthread_mutex_lock(&(info->print_mutex));
	if (!(info->dead))
		printf("%lld %d %s\n", timestamp() - info->time_to_start,
			philo_idx, str);
	pthread_mutex_unlock(&(info->print_mutex));
}

int	eat_spaghetti(t_setting *info, t_philo *philo)
{
	
	return(0);
}

int	have_forks(t_setting *info, t_philo *philo) {
	if (info->forks[philo->idx].state == USED
		 || info->forks[(philo->idx + 1) % info->philo_num].state == USED)
		 	return 0;
	pthread_mutex_lock(&(info->forks[philo->idx].mutex));
	info->forks[philo->idx].state = USED;
	print(info, "has taken a fork", philo->idx + 1);
	pthread_mutex_lock(&(info->forks[(philo->idx + 1)
			% (info->philo_num)].mutex));
	info->forks[(philo->idx + 1) % (info->philo_num)].state = USED;
	print(info, "has taken a fork", philo-> idx + 1);
	// printf("%s has taken a fork", philo->idx);
	eat_spaghetti(info, philo);
	pthread_mutex_unlock(&(info->forks[philo->idx].mutex));
	pthread_mutex_unlock(&(info->forks[(philo->idx + 1)
			% (info->philo_num)].mutex));
	// if (info->eat)
	return (1);
}

// void	sleep_time(t_setting *info)
// {
// 	long long	sleep_time;
	
// }

void	ft_usleep(int mili_second)
{
	long long	time;

	time = timestamp();
	usleep(mili_second * 900);
	while (timestamp() < time + mili_second)
		usleep(20);
}

void	*execute_philo(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	if (philo->idx % 2 == 0)
		usleep(3000);//데드락 피하기 - 30000정도로 설정해도 될듯 암튼 실험해봤을 때는 가능
	while (!(philo->common_info->dead))
	{
		if (have_forks(philo->common_info, philo))
			break ;
		print(philo->common_info, "is sleeping", philo->idx);
		ft_usleep(philo->common_info->time_to_sleep);
		print(philo->common_info, "is thinking", philo->idx);
	}
	// printf("%d\n", philo->idx);
	return(NULL);
}