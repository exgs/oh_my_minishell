/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunslee <yunslee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 15:43:51 by yunslee           #+#    #+#             */
/*   Updated: 2020/04/16 18:18:00 by yunslee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static unsigned int	ft_strlen(const char *s)
{
	unsigned int i;

	i = 0;
	while (s[i])
	{
		i++;
	}
	return (i);
}

size_t				ft_strlcat(char *dest, const char *src, size_t size)
{
	unsigned int i;
	unsigned int j;
	unsigned int dst_len;
	unsigned int src_len;

	src_len = ft_strlen(src);
	if (size == 0)
		return (src_len + size);
	dst_len = ft_strlen(dest);
	i = dst_len;
	j = 0;
	while (i < size - 1 && j < src_len)
	{
		dest[i++] = src[j++];
	}
	if (size > dst_len)
	{
		dest[i] = '\0';
		return (src_len + dst_len);
	}
	else
		return (src_len + size);
}
