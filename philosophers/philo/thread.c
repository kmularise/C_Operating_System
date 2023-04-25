/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuikim <yuikim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 08:25:18 by yuikim            #+#    #+#             */
/*   Updated: 2023/04/07 13:22:48 by yuikim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"


void	ft_pass_time(int mili_second)
{
	long long	time;

	time = timestamp();
	while (timestamp() < time + (long long)mili_second)
		usleep(10);
}

void	print(t_setting *info, char *str, int philo_idx)
{
	pthread_mutex_lock(&(info->print_mutex));
	if (!(info->dead))
		printf("%lld %d %s\n", timestamp() - info->time_to_start,
			philo_idx, str);
	pthread_mutex_unlock(&(info->print_mutex));
}

//mutex lock 써서 걸기
int	have_forks(t_setting *info, t_philo *philo) {
	pthread_mutex_lock(&(info->forks[philo->idx].mutex));
	if (info->forks[philo->idx].state == USED)
	{
		pthread_mutex_unlock(&(info->forks[philo->idx].mutex));
		return (-1);
	}
	info->forks[philo->idx].state = USED;
	print(info, "has taken a fork", philo->idx + 1);
	pthread_mutex_lock(&(info->forks[(philo->idx + 1)
			% (info->philo_num)].mutex));
	if (info->forks[(philo->idx + 1) % (info->philo_num)].state == USED)
	{
		pthread_mutex_unlock(&(info->forks[(philo->idx + 1)
			% (info->philo_num)].mutex));
		pthread_mutex_unlock(&(info->forks[philo->idx].mutex));
	}
	info->forks[(philo->idx + 1) % (info->philo_num)].state = USED;
	print(info, "has taken a fork", philo-> idx + 1);
	// print(info, "is eating", philo-> idx + 1);//eat 관련해서 만들기..
	eat(philo, info);
	philo->last_eat = timestamp();
	philo->eat_count = philo->eat_count + 1;
	pthread_mutex_unlock(&(info->forks[(philo->idx + 1)
			% (info->philo_num)].mutex));
	pthread_mutex_unlock(&(info->forks[philo->idx].mutex));
	return (1);
}

static void	choose_forks(t_philo *philo, t_setting *info, int *fork1, int *fork2)
{
	int	flag;

	if (philo->idx % 2 == 1)
	{
		if (info->philo_num % 2 == 1)//홀수
			flag = 0;
		else
			flag = 1;
	}
	else
	{
		if (info->philo_num % 2 == 1)
			flag = 1;
		else
			flag = 0;
	}
	if (flag)
	{
		*fork1 = (philo->idx + 1) % (info->philo_num);
		*fork2 = philo->idx;
		return ;
	}
	*fork1 = philo->idx;
	*fork2 = (philo->idx + 1) % (info->philo_num);
}

static void	set_forks(t_philo *philo, t_setting *info)
{
	int	fork1;
	int	fork2;

	choose_forks(philo, info, &fork1, &fork2);
	pthread_mutex_lock(&(info->forks[fork1].mutex));
	pthread_mutex_lock(&info->print_mutex);
	printf("%lld %d has taken fork(%d)\n",timestamp(), philo->idx, fork1);
	pthread_mutex_unlock(&info->print_mutex);
	// pthread_mutex_unlock(&(info->forks[fork1].mutex));
	pthread_mutex_lock(&(info->forks[fork2].mutex));
	pthread_mutex_lock(&info->print_mutex);
	printf("%lld %d has taken fork(%d)\n",timestamp(), philo->idx, fork2);
	pthread_mutex_unlock(&info->print_mutex);
	// pthread_mutex_unlock(&(info->forks[fork1].mutex));
}

void	eat(t_philo *philo, t_setting *info)
{
	philo->eat_count++;
	philo->last_eat = timestamp();
	ft_pass_time(info->time_to_eat);
}

void	*execute_philo(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	while(1)
	{
		set_forks(philo, philo->common_info);
		pthread_mutex_lock(&philo->common_info->print_mutex);
		printf("%lld %d is eating\n", timestamp(), philo->idx);
		pthread_mutex_unlock(&philo->common_info->print_mutex);

		
		// have_forks(philo->common_info, philo);
		// print(philo->common_info, "is sleeping", philo->idx + 1);
		// ft_pass_time(philo->common_info->time_to_sleep);
		// print(philo->common_info, "is thinking", philo->idx + 1);
	}
	// printf("%d\n", philo->idx);
	return(NULL);
}