/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_minishell.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunslee <yunslee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 03:57:15 by yunslee           #+#    #+#             */
/*   Updated: 2021/01/27 18:59:37 by yunslee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t		split_len(const char *s, char c)
{
	unsigned int i;
	char flag_quotes;

	flag_quotes = 0;
	if (s[0] == '\'')
		flag_quotes ^= 1;
	if (s[0] == '\"')
		flag_quotes ^= 2;
	i = 1;
	while ((s[i] && s[i] != c) || (flag_quotes & 0x3))
	{
		if (s[i - 1] != '\\')
		{
			if (s[i] == '\'')
				flag_quotes ^= 1;
			if (s[i] == '\"')
				flag_quotes ^= 2;
		}
		i++;
	}
	return (i);
}

static unsigned int	size_array(const char *str, char c)
{
	int size;
	int i;
	char flag_quotes;

	i = 0;
	size = 0;
	if (str[0] == '\0')
		return (size);
	if (str[0] != c)
		size = 1;
	flag_quotes = 0;
	if (str[0] == '\'')
		flag_quotes ^= 1;
	if (str[0] == '\"')
		flag_quotes ^= 2;
	i = 1;
	while (str[i])
	{
		if (str[i - 1] != '\\')
		{
			if (str[i] == '\'')
				flag_quotes ^= 1;
			if (str[i] == '\"')
				flag_quotes ^= 2;
		}
		if ((str[i] == c && str[i + 1] != c) && str[i + 1] != 0 &&
				(flag_quotes ^ 0x1) && (flag_quotes ^ 0x2))
			size++;
		i++;
	}
	return (size);
}

static int			input_parts(char *dst, const char *src, char c, int i)
{
	int j;
	char flag_quotes;

	j = 0;
	flag_quotes = 0;
	while ((src[i] && src[i] != c) || (flag_quotes & 0x3))
	{
		if (i != 0 && src[i - 1] != '\\')
		{
			if (src[i] == '\'')
				flag_quotes ^= 1;
			if (src[i] == '\"')
				flag_quotes ^= 2;
		}
		dst[j] = src[i];
		j++;
		i++;
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

char				**ft_split_minishell(char const *s, char c)
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
		row++;
	}
	split[array_size] = NULL;
	return (split);
}
