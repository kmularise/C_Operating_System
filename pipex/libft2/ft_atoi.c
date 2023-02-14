/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuikim <yuikim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 19:55:36 by yuikim            #+#    #+#             */
/*   Updated: 2022/11/19 09:19:56 by yuikim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	check_digit(char ch)
{
	if ('0' <= ch && ch <= '9')
		return (1);
	return (0);
}

int	ft_atoi(const char *str)
{
	long long	num;
	int			i;
	int			sign;

	num = 0;
	sign = 1;
	i = 0;
	while ((9 <= str[i] && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (check_digit(str[i]))
	{
		if (sign * num > 2147483647)
			return (-1);
		if (sign * num < -2147483648)
			return (0);
		num = (str[i] - '0') + num * 10;
		i++;
	}
	return (sign * num);
}
