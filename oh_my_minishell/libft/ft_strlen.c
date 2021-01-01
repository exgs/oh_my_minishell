/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunslee <yunslee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 18:05:36 by yunslee           #+#    #+#             */
/*   Updated: 2020/07/25 20:21:10 by yunslee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	ft_strlen(const char *s)
{
	unsigned int i;

	if (s == NULL)
		return (-1);
	i = 0;
	while (s[i])//s가 NULL일 때, 처리를 해주지 않아서 segfault뜨기 쉬움, 실제로 strlen(NULL)-> segfault.
	{
		i++;
	}
	return (i);
}
