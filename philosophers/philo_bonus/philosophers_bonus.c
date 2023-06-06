/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuikim <yuikim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 14:21:45 by yuikim            #+#    #+#             */
/*   Updated: 2023/06/06 22:03:01 by yuikim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

int	main(int argc, char **argv)
{
	t_philo	philo;

	if (check_valid_input(argc, argv) == 1)
		return (0);
	if (initiate_setting(&philo, argv) == 1)
		return (0);
	init_semaphores(&philo);
	create_philos(&philo);
}
