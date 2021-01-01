/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunslee <yunslee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 17:44:30 by yunslee           #+#    #+#             */
/*   Updated: 2020/04/10 21:51:38 by yunslee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	ft_strncmp(const char *s1, const char *s2, size_t len)
{
	unsigned int	i;
	unsigned char	*ss1;
	unsigned char	*ss2;

	ss1 = (unsigned char *)s1;
	ss2 = (unsigned char *)s2;
	i = 0;
	while (ss1[i] && ss2[i] && (i < len))
	{
		if (ss1[i] - ss2[i] != 0)
			return (ss1[i] - ss2[i]);
		i++;
	}
	if (i == len)
		return (0);
	return (ss1[i] - ss2[i]);
}
