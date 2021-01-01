/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunslee <yunslee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 21:53:28 by yunslee           #+#    #+#             */
/*   Updated: 2020/04/13 22:29:48 by yunslee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static size_t	ft_strlen2(const char *s)
{
	unsigned int i;

	i = 0;
	while (s[i])
	{
		i++;
	}
	return (i);
}

char			*ft_strjoin(char const *head, char const *tail)
{
	char *join;
	int total_len;
	int head_len;
	int i;

	if (head == NULL && tail == NULL)
		return (NULL);
	else if (head == NULL)
		return (ft_strdup(tail));
	else if (tail == NULL)
		return (ft_strdup(head));
	i = 0;
	total_len = ft_strlen2(head) + ft_strlen2(tail);
	head_len = ft_strlen2(head);
	join = malloc(sizeof(char) * (total_len + 1));
	while (i < total_len)
	{
		if (i < head_len)
			join[i] = head[i];
		else
			join[i] = tail[i - head_len];
		i++;
	}
	join[i] = '\0';
	return (join);
}
