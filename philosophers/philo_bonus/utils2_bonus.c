/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuikim <yuikim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 21:02:11 by yuikim            #+#    #+#             */
/*   Updated: 2023/06/06 22:01:11 by yuikim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	print(t_philo *philo, char *message)
{
	sem_wait(philo->print);
	printf("%lld %d %s\n", timestamp() - philo->time_to_start,
		philo->idx + 1, message);
	sem_post(philo->print);
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
