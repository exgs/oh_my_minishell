/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunslee <yunslee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 21:32:48 by yunslee           #+#    #+#             */
/*   Updated: 2020/04/18 02:10:42 by yunslee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static unsigned int		ft_strlen(const char *s)
{
	unsigned int i;

	i = 0;
	while (s[i])
	{
		i++;
	}
	return (i);
}

char			*ft_substr(char *s, unsigned int start, size_t len)
{
	unsigned int	i;
	char			*substring;

	if (s == NULL)
		return (NULL);
	if (start >= ft_strlen(s))
	{
		substring = (char *)malloc(sizeof(char) * 1);
		*substring = '\0';
		return (substring);
	}
	if (start + len > ft_strlen(s))
		substring = (char *)malloc(sizeof(char) * (ft_strlen(s) - start + 1));
	else
		substring = (char *)malloc(sizeof(char) * (len + 1));
	i = 0;
	if (substring == NULL)
		return (NULL);
	while (i < len && s[start + i] != '\0')
	{
		substring[i] = s[start + i];
		i++;
	}
	substring[i] = '\0';
	return (substring);
}
