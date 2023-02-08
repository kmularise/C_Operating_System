/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuikim <yuikim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 09:52:53 by yuikim            #+#    #+#             */
/*   Updated: 2023/02/08 14:17:38 by yuikim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char *s, int start, int len)
{
	char	*answer;
	int		substr_len;
	int		i;

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
