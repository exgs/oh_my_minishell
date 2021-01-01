/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunslee <yunslee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 09:59:58 by yunslee           #+#    #+#             */
/*   Updated: 2020/04/13 22:29:25 by yunslee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_memcpy(void *dst, const void *src, size_t len)
{
	unsigned char	*str1;
	unsigned char	*str2;
	unsigned int	i;

	if (src == 0 && dst == 0)
		return (dst);
	str1 = (unsigned char*)dst;
	str2 = (unsigned char*)src;
	i = 0;
	while (i < len)
	{
		str1[i] = str2[i];
		i++;
	}
	return (dst);
}
