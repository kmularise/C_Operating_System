/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuikim <yuikim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 19:57:22 by yuikim            #+#    #+#             */
/*   Updated: 2023/04/06 20:03:54 by yuikim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long long	timestamp(void)
{
	long long		ms_time;
	struct timeval	standard_time;

	gettimeofday(&standard_time, NULL);
	ms_time = standard_time.tv_sec * 1000 + standard_time.tv_usec / 1000;
	return (ms_time);
}

