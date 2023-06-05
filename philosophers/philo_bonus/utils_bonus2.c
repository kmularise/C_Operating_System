/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuikim <yuikim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 21:02:11 by yuikim            #+#    #+#             */
/*   Updated: 2023/06/05 19:21:55 by yuikim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	print(t_philo *philo, char *message)
{
	sem_wait(philo->print);
	printf("%lld %d %s", philo->idx + 1, timestamp() - philo->time_to_start);
	sem_post(philo->print);
}

int	is_dead(t_philo *philo)
{
	int	dead;

	sem_wait(philo->die);
	dead = philo->dead;	
	sem_post(philo->die);
	return (dead);
}

void	set_dead(t_philo *philo)
{
	sem_wait(philo->die);
	philo->dead = 1;
	sem_post(philo->die);
}

void	ft_usleep(int mili_second)
{
	long long	time;
	long long	now;

	time = timestamp();
	now = time;
	while (now < time + (long long)mili_second)
	{
		usleep(1000);
		now = timestamp();
	}
}
