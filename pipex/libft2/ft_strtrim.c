/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuikim <yuikim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 10:34:59 by yuikim            #+#    #+#             */
/*   Updated: 2022/11/19 09:01:58 by yuikim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_contain(char ch, char const *set)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (ch == set[i])
			return (1);
		i++;
	}
	return (0);
}

static size_t	ft_trim_len_left(char const *s1, char const *set)
{
	size_t	i;

	i = 0;
	while (ft_contain(s1[i], set) && s1[i])
	{
		i++;
	}
	return (i);
}

static size_t	ft_trim_len_right(char const *set,
						char const *s1, size_t s1_len, size_t left_trim_len)
{
	size_t	i;
	size_t	len;

	if (s1_len == left_trim_len)
		return (0);
	i = s1_len - 1;
	len = 0;
	while (ft_contain(s1[i], set) == 1 && i >= 0)
	{
		i--;
		len++;
	}
	return (len);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*answer;
	size_t	s1_len;
	size_t	left_trim_len;
	size_t	right_trim_len;
	size_t	i;

	s1_len = ft_strlen(s1);
	left_trim_len = ft_trim_len_left(s1, set);
	right_trim_len = ft_trim_len_right(set, s1, s1_len, left_trim_len);
	answer = (char *)malloc(sizeof(char) * (s1_len
				- left_trim_len - right_trim_len + 1));
	if (!answer)
		return (NULL);
	i = 0;
	while (i < s1_len - right_trim_len - left_trim_len)
	{
		answer[i] = s1[i + left_trim_len];
		i++;
	}
	answer[i] = 0;
	return (answer);
}
