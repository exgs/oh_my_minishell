/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jikang <jikang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 16:24:46 by yunslee           #+#    #+#             */
/*   Updated: 2021/01/29 16:44:27 by jikang           ###   ########.fr       */
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

char			*ft_strrchr(const char *s, int c)
{
	unsigned int	i;
	size_t			strlen;
	char			*str;

	if (NULL == (str = (char *)s))
		return (NULL);
	strlen = ft_strlen(s);
	if (c == 0)
		return (str + strlen);
	i = 0;
	while (i < strlen)
	{
		if (s[(strlen - 1) - i] == (unsigned char)c)
			return (str + (strlen - 1) - i);
		i++;
	}
	return (NULL);
}
