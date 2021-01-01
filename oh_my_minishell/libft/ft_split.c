/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunslee <yunslee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 14:22:04 by yunslee           #+#    #+#             */
/*   Updated: 2020/04/16 17:14:43 by yunslee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static size_t		split_len(const char *s, char c)
{
	unsigned int i;

	i = 0;
	while (s[i] && s[i] != c)
	{
		i++;
	}
	return (i);
}

static unsigned int	size_array(const char *str, char c)
{
	int size;
	int i;

	i = 0;
	size = 0;
	if (str[0] == '\0')
		return (size);
	if (str[0] != c)
		size += 1;
	while (str[i])
	{
		if ((str[i] == c && str[i + 1] != c) && str[i + 1] != 0)
			size++;
		i++;
	}
	return (size);
}

static int			input_parts(char *dst, const char *src, char c, int i)
{
	int j;

	j = 0;
	while (src[i] && src[i] != c)
	{
		dst[j] = src[i];
		i++;
		j++;
	}
	dst[j] = '\0';
	return (i);
}

static void			free_all(char **split)
{
	char **split_init;

	split_init = split;
	while (*split != NULL)
	{
		free(*split);
		split++;
	}
	free(split_init);
}

char				**ft_split(char const *s, char c)
{
	unsigned int	i;
	unsigned int	array_size;
	unsigned int	row;
	char			**split;

	i = 0;
	row = 0;
	array_size = size_array(s, c);
	if (NULL == (split = (char**)malloc(sizeof(char *) * (array_size + 1))))
		return (NULL);
	while (row < array_size)
	{
		while (s[i] == c)
			i++;
		if (NULL == (split[row] = malloc(sizeof(char) *
									(split_len((s + i), c) + 1))))
		{
			free_all(split);
			return (NULL);
		}
		i = input_parts(split[row], s, c, i);
		/*
		**함수내에서 split된 문자를 집어넣으면서 증가시킨 i 값을 return함
		**static int 을 이용할 수도 있을 거 같다는 생각이 듦...
		*/
		row++;
	}
	split[array_size] = NULL;
	return (split);
}
