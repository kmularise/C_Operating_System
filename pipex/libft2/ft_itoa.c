/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuikim <yuikim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 16:00:01 by yuikim            #+#    #+#             */
/*   Updated: 2022/11/19 09:03:01 by yuikim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_find_number_figure(long long n)
{
	size_t		i;
	long long	n1;

	n1 = (long long)n;
	if (n1 < 0)
		return (ft_find_number_figure(-n1) + 1);
	i = 0;
	while (1)
	{
		i++;
		if (n1 / 10 == 0)
			return (i);
		n1 = n1 / 10;
	}
	return (0);
}

static void	ft_assign(long long n, char *answer, size_t figure)
{
	size_t	i;
	char	digit;

	i = figure - 1;
	if (n < 0)
	{
		answer[0] = '-';
		n = -n;
	}
	while (1)
	{
		digit = n % 10 + '0';
		answer[i] = digit;
		if (n / 10 == 0)
			break ;
		i--;
		n = n / 10;
	}
	answer[figure] = 0;
}

char	*ft_itoa(int n)
{
	char	*answer;
	size_t	figure;

	figure = ft_find_number_figure((long long)n);
	answer = (char *)malloc(sizeof(char) * (figure + 1));
	if (!answer)
		return (NULL);
	ft_assign((long long)n, answer, figure);
	return (answer);
}
