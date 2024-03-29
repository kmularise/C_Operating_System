/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuikim <yuikim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 14:21:45 by yuikim            #+#    #+#             */
/*   Updated: 2023/06/01 20:37:24 by yuikim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

pthread_t	*create_phillosophers(char *philo_num)
{
	pthread_t	*philosophers;
	int			size;

	size = ft_atoi(philo_num);
	philosophers = malloc(sizeof(pthread_t) * (size + 1));
	philosophers[size] = NULL;
	return (philosophers);
}

t_thread_info	*create_thread_info_node(int idx)
{
	t_thread_info	*node;

	node = malloc(sizeof(t_thread_info));
	node->idx = idx;
	return (node);
}

t_thread_info	**create_thread_info_arr(char *philo_num)
{
	t_thread_info	**info_arr;
	int				size;
	int				i;

	size = ft_atoi(philo_num);
	info_arr = malloc(sizeof(t_thread_info *) * (size + 1));
	i = -1;
	while (++i < size)
		info_arr[i] = create_thread_info_node(i);
	info_arr[size] = NULL;
	return (info_arr);
}

t_common_resource	*create_common_resource(char *philo_num)
{
	t_common_resource	*common_resource;
	int					*forks;
	int					size;
	int					i;

	common_resource = malloc(sizeof(t_common_resource));
	size = ft_atoi(philo_num);
	forks = malloc(sizeof(char) * (size + 1));
	i = -1;
	while (++i < size)
		forks[i] = AVAILABLE;
	forks[size] = 0;
	common_resource->forks = forks;
	common_resource->info_arr = create_thread_info_arr(philo_num);
	return (common_resource);
}

int	main(int argc, char **argv)
{
	t_setting			setting;

	if (check_valid_input(argc, argv) == 1)
		return (0);
	if (initiate_setting(&setting, argv) == 1)
		return (0);
	initiate_philos(&setting);
}
