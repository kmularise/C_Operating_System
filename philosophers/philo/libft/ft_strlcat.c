/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuikim <yuikim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 10:11:55 by yuikim            #+#    #+#             */
/*   Updated: 2022/11/11 10:28:05 by yuikim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, char *src, size_t dstsize)
{
	size_t	dest_len;
	size_t	src_len;
	size_t	i;

	dest_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	i = 0;
	if (dstsize < dest_len)
		return (src_len + dstsize);
	while (src[i] && (i + dest_len + 1 < dstsize))
	{
		dst[i + dest_len] = src[i];
		i++;
	}
	dst[i + dest_len] = 0;
	return (src_len + dest_len);
}
