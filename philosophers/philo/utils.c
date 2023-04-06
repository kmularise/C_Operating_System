/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuikim <yuikim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 11:07:08 by yuikim            #+#    #+#             */
/*   Updated: 2023/04/06 19:42:44 by yuikim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	is_positive_num(char *str)
{
	int	i;
	int	j;

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
			return(show_error("invalid input\n"));
	}
	if (ft_atoi(argv[1]) > 200)
		return(show_error("test failure : philosophers more than 200"));
	return (0);
}
