/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuikim <yuikim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 10:08:05 by yuikim            #+#    #+#             */
/*   Updated: 2023/01/04 18:24:08 by yuikim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char *s1, char *s2)
{
	char	*answer;
	size_t	s1_len;
	size_t	s2_len;
	size_t	i;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	answer = malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (!answer)
		return (NULL);
	i = 0;
	while (i < s1_len)
	{
		answer[i] = s1[i];
		i++;
	}
	i = 0;
	while (i < s2_len)
	{
		answer[s1_len + i] = s2[i];
		i++;
	}
	answer[s1_len + i] = 0;
	return (answer);
}
