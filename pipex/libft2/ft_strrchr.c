/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuikim <yuikim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 18:26:46 by yuikim            #+#    #+#             */
/*   Updated: 2022/11/23 08:21:23 by yuikim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t		i;
	char		*ptr;

	i = 0;
	ptr = NULL;
	while (i < ft_strlen(s) + 1)
	{
		if (s[i] == (char)c)
			ptr = (char *)s + i;
		i++;
	}
	return (ptr);
}
