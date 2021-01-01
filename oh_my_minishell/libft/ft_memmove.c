/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunslee <yunslee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 19:51:19 by yunslee           #+#    #+#             */
/*   Updated: 2020/04/13 22:30:05 by yunslee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char		*str1;
	const unsigned char	*str2;
	unsigned int		i;

	if (dst == 0 && src == 0)
		return (dst);
	str1 = (unsigned char*)dst;
	str2 = (const unsigned char*)src;
	i = 0;
	if (str1 < str2)
		while (i < len)
		{
			str1[i] = str2[i];
			i++;
		}
	else
	{
		while (i < len)
		{
			str1[(len - 1) - i] = str2[(len - 1) - i];
			i++;
		}
	}
	return (dst);
}
