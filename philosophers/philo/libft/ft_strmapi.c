/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuikim <yuikim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 10:25:03 by yuikim            #+#    #+#             */
/*   Updated: 2022/11/23 08:17:34 by yuikim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*answer;
	unsigned int	i;

	answer = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!answer)
		return (NULL);
	i = 0;
	while (i < ft_strlen(s))
	{
		answer[i] = f(i, s[i]);
		i++;
	}
	answer[i] = 0;
	return (answer);
}
