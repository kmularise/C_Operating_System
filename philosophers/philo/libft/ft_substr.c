/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuikim <yuikim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 09:52:53 by yuikim            #+#    #+#             */
/*   Updated: 2022/11/25 11:03:01 by yuikim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*answer;
	size_t	substr_len;
	size_t	i;

	substr_len = 0;
	if (start < ft_strlen(s))
	{
		while (s[start + substr_len] && substr_len < len)
			substr_len++;
	}
	answer = (char *)malloc(sizeof(char) * (substr_len + 1));
	if (!answer)
		return (NULL);
	i = 0;
	while (i < substr_len)
	{
		answer[i] = s[start + i];
		i++;
	}
	answer[i] = 0;
	return (answer);
}
