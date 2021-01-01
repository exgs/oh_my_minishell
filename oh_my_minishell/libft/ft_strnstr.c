/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunslee <yunslee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 14:11:12 by yunslee           #+#    #+#             */
/*   Updated: 2020/04/10 02:54:44 by yunslee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static size_t	ft_strlen(const char *s)
{
	unsigned int i;

	i = 0;
	while (s[i])
	{
		i++;
	}
	return (i);
}

char			*ft_strnstr(const char *big, const char *little, size_t n)
{
	unsigned int	i;
	unsigned int	j;
	unsigned int	little_len;
	char			*str;

	str = (char *)big;
	if (little[0] == '\0')
		return (str);
	little_len = ft_strlen(little);
	i = 0;
	while (str[i] && str[i + (little_len - 1)] && (i + (little_len - 1)) < n)
	{
		j = 0;
		while (little[j])
		{
			if (str[i + j] != little[j])
				break ;
			if (j == little_len - 1)
				return (str + i);
			j++;
		}
		i++;
	}
	return (NULL);
}
