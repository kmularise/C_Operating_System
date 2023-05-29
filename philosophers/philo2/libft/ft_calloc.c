/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuikim <yuikim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 09:17:00 by yuikim            #+#    #+#             */
/*   Updated: 2022/11/14 20:12:42 by yuikim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	char	*answer;

	answer = (char *)malloc(count * size * sizeof(*answer));
	if (!answer)
		return (NULL);
	ft_memset(answer, 0, count * size);
	return (answer);
}
