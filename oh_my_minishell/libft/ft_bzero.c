/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunslee <yunslee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 20:53:26 by yunslee           #+#    #+#             */
/*   Updated: 2020/04/11 16:21:10 by yunslee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	ft_bzero(void *b, size_t len)
{
	unsigned int	i;
	unsigned char	*str;

	i = 0;
	str = b;
	while (i < len)
	{
		str[i] = 0;
		i++;
	}
}
