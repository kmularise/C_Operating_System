/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuikim <yuikim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 11:07:08 by yuikim            #+#    #+#             */
/*   Updated: 2023/06/28 11:54:36 by yuikim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

static int	is_positive_num(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	show_error(char *message)
{
	ft_putstr_fd(message, 2);
	return (1);
}

int	check_valid_input(int argc, char **argv)
{
	int	i;

	i = 0;
	if (argc != 5 && argc != 6)
		return (show_error("invalid input\n"));
	while (argv[++i])
	{
		if (!is_positive_num(argv[i]) || ft_atoi(argv[i]) == -1)
			return (show_error("invalid input\n"));
	}
	if (ft_atoi(argv[1]) > 200)
		return (show_error("test failure : philosophers more than 200"));
	return (0);
}

long long	timestamp(void)
{
	long long		ms_time;
	struct timeval	standard_time;

	gettimeofday(&standard_time, NULL);
	ms_time = standard_time.tv_sec * 1000 + standard_time.tv_usec / 1000;
	return (ms_time);
}
