/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuikim <yuikim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 21:02:11 by yuikim            #+#    #+#             */
/*   Updated: 2023/06/02 21:10:10 by yuikim           ###   ########.fr       */
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


