/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunslee <yunslee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 15:44:09 by yunslee           #+#    #+#             */
/*   Updated: 2020/04/16 18:22:53 by yunslee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_memchr(const void *b, int c, size_t len)
{
	size_t			i;
	unsigned char	*str;

	if (b == NULL)
		return (NULL);
	str = (unsigned char*)b;
	i = 0;
	while (i < len)
	{
		if (str[i] == (unsigned char)c)
			return (str + i);
		i++;
	}
	return (NULL);
}
