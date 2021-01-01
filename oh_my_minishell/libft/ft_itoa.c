/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunslee <yunslee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 15:24:19 by yunslee           #+#    #+#             */
/*   Updated: 2020/04/13 22:10:55 by yunslee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int		ft_itoa_len(int v)
{
	int i;

	i = 0;
	if (v == 0)
		return (1);
	if (v < 0)
		i = 1;
	while (v != 0)
	{
		v /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char	*itoa;
	int		itoa_len;
	int		i;
	int		temp;

	i = 1;
	itoa_len = ft_itoa_len(n);
	if (NULL == (itoa = (char *)malloc(sizeof(char) * (itoa_len + 1))))
		return (NULL);
	if (n < 0)
		itoa[0] = '-';
	else if (n == 0)
		itoa[0] = '0';
	itoa[itoa_len] = '\0';
	while (n != 0)
	{
		temp = n % 10;
		if (temp < 0)
			temp *= -1;
		itoa[itoa_len - i] = temp + '0';
		n /= 10;
		i++;
	}
	return (itoa);
}
