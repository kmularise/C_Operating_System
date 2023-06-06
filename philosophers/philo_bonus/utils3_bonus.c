/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuikim <yuikim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 20:50:11 by yuikim            #+#    #+#             */
/*   Updated: 2023/06/06 15:34:20 by yuikim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

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
		num = (str[i] - '0') + num * 10;
		i++;
	}
	if (num > 2147483647)
		return (-1);
	return (sign * num);
}

int	ft_isdigit(int c)
{
	return ('0' <= c && c <= '9');
}

void	ft_putstr_fd(char *s, int fd)
{
	if (!s)
		return ;
	write(fd, s, ft_strlen(s));
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		i++;
	}
	return (i);
}
