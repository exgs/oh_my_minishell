/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunslee <yunslee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 18:47:34 by yunslee           #+#    #+#             */
/*   Updated: 2020/04/13 19:03:36 by yunslee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_memccpy(void *dst, const void *src, int c, size_t len)
{
	size_t			i;
	char			*str1;
	const char		*str2;

	str1 = (char *)dst;
	str2 = (const char *)src;
	i = 0;
	while (i < len)
	{
		str1[i] = str2[i];
		if (str1[i] == (char)c)
			return (str1 + i + 1);
		i++;
	}
	return (NULL);
}
