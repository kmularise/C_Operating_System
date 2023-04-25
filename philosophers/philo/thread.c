/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuikim <yuikim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 08:25:18 by yuikim            #+#    #+#             */
/*   Updated: 2023/04/25 18:43:07 by yuikim           ###   ########.fr       */
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

void	eat_spaghetti(t_setting *info)
{
	long long	start_eat;
	long long	now;

	start_eat = timestamp();
	while (!info->dead)
	{
		now = timestamp();
		if (now - start_eat >= (long long)(info->time_to_eat))
			break ;
		usleep(10);
	}
}

// int	get_total_eat(t_setting *info) {
// 	int	turn;

// 	pthread_mutex_lock(&(info->total_eat_mutex));
// 	turn = info->total_eat;
// 	pthread_mutex_unlock(&(info->total_eat_mutex));
// 	return turn;
// }

void	eat(t_setting *info, t_philo *philo)
{
	// pthread_mutex_lock(&(info->total_eat_mutex));
	// (info->total_eat)++;
	// pthread_mutex_unlock(&(info->total_eat_mutex));

	pthread_mutex_lock(&(info->eat_mutex));//total_eat turn를 측정
	print(info, "is eating", philo->idx + 1);
	philo->start_eat = timestamp();
	pthread_mutex_unlock(&(info->eat_mutex));
	philo
	(philo->eat_count)++;
	eat_spaghetti(info);

	//몰루
}

int	have_forks(t_setting *info, t_philo *philo) {
	//차례를 지정해주는 방법이 있음 짝수 홀수 나눠서 생각하기 total_eat turn를 지정
	pthread_mutex_lock(&(info->forks[philo->idx].mutex));//lock unlock를 이 fork에 한해서
	print(info, "has taken a fork", philo->idx + 1);
	pthread_mutex_unlock(&(info->forks[philo->idx].mutex));

	pthread_mutex_lock(&(info->forks[(philo->idx + 1)
			% (info->philo_num)].mutex));
	print(info, "has taken a fork", philo-> idx + 1);
	pthread_mutex_unlock(&(info->forks[(philo->idx + 1)
		% (info->philo_num)].mutex));
	eat(info, philo);
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
	while (timestamp() < time + (long long)mili_second)
		usleep(20);
}

int	get_turn(t_setting *info) {
	int	turn;

	pthread_mutex_lock(&(info->total_eat_mutex));
	turn = info->turn;
	pthread_mutex_unlock(&(info->total_eat_mutex));
	return (turn);
}

int set_turn(t_setting *info) {
	int	turn;

	pthread_mutex_lock(&(info->total_eat_mutex));
	(info->turn)++;
	pthread_mutex_unlock(&(info->total_eat_mutex));
	return 0;
}


int is_turn(t_philo *philo, t_setting *info) {
	//구조체에 저장 추가하기
	int	turn;
	int	total_count;

	total_count = get_turn(info);
	set_turn(info);
	turn = total_count / info->philo_num;
	if (info->philo_num % 2 == 0)
	{
		if (turn % 2 == 0 && philo->idx % 2 == 0)
			return 1;
		if (turn % 2 != 0 && philo->idx % 2 == 1)
			return 1;
		return 0;
	}
	if (turn % 3 == 0 && philo->idx % 2 == 0 && philo->idx != info->philo_num - 1)
		return (1);
	if (turn % 3 == 1 && philo->idx % 2 == 1)
		return (1);
	if (turn % 3 == 2 && philo->idx == info->philo_num - 1)
		return (1);
	return (0);
}



void	*execute_philo(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	while (1)
	{
		if (is_turn(philo, philo->common_info))
		{
			have_forks(philo->common_info, philo);
		}
		print(philo->common_info, "is sleeping", philo->idx + 1);
		ft_usleep(philo->common_info->time_to_sleep);
		print(philo->common_info, "is thinking", philo->idx + 1);//thinking하기
	}
	// printf("%d\n", philo->idx);
	return(NULL);
}