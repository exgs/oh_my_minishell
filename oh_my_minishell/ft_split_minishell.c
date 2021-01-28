/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_minishell.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunslee <yunslee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 03:57:15 by yunslee           #+#    #+#             */
/*   Updated: 2021/01/29 04:47:19 by yunslee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t		split_len(const char *str, char c)
{
	unsigned int i;
	char flag_quotes;

	flag_quotes = 0;
	if (str[0] == '\0' || str[0] == c)
		return (0);
	else if (str[0] == '\'')
		flag_quotes ^= 1;
	else if (str[0] == '\"')
		flag_quotes ^= 2;
	if ((str[1] == '\0' || str[1] == c) && (flag_quotes ^ 0x1 && flag_quotes ^ 0x2))
		return (1);
	else if (str[1] == '\'' && str[0] != '\\')
		flag_quotes ^= 1;
	else if (str[1] == '\"' && str[0] != '\\')
		flag_quotes ^= 2;
	i = 2;
	while ((str[i] && str[i] != c) || flag_quotes & 0x3)
	{
		if (str[i] == '\0')
			break;
		if (str[i - 1] != '\\')
		{
			if (str[i] == '\'')
				flag_quotes ^= 1;
			if (str[i] == '\"')
				flag_quotes ^= 2;
		}
		if (str[i - 1] == '\\' && str[i - 2] == '\\')
		{
			if (str[i] == '\'')
				flag_quotes ^= 1;
			if (str[i] == '\"')
				flag_quotes ^= 2;
		}
		i++;
	}
	// printf("len:%d\n", i);
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
		size += 1;
	flag_quotes = 0;
	if (str[0] == '\'')
		flag_quotes ^= 1;
	if (str[0] == '\"')
		flag_quotes ^= 2;
	if (str[1] == '\'' && str[0] != '\\')
		flag_quotes ^= 1;
	if (str[1] == '\"' && str[0] != '\\')
		flag_quotes ^= 2;
	if (str[1] != c && str[0] == c)
		size += 1;
	i = 2;
	while (str[i])
	{
		if (str[i - 1] != '\\')
		{
			if (str[i] == '\'')
				flag_quotes ^= 1;
			if (str[i] == '\"')
				flag_quotes ^= 2;
		}
		if (str[i - 1] == '\\' && str[i - 2] == '\\')
		{
			if (str[i] == '\'')
				flag_quotes ^= 1;
			if (str[i] == '\"')
				flag_quotes ^= 2;
		}
		if (((str[i] == c && str[i + 1] != c) && str[i + 1] != 0) &&
				(flag_quotes ^ 0x1) && (flag_quotes ^ 0x2))
			size++;
		i++;
	}
	// printf("size:%d\n",size);
	return (size);
}

static int			input_parts(char *dst, const char *src, int size, int i)
{
	int j;

	j = 0;
	while (j < size)
	{
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

char				**ft_split_minishell(char const *str, char c)
{
	unsigned int	i;
	unsigned int	array_size;
	unsigned int	row;
	char			**split;

	i = 0;
	row = 0;
	array_size = size_array(str, c);
	if (NULL == (split = (char**)malloc(sizeof(char *) * (array_size + 1))))
		return (NULL);
	while (row < array_size)
	{
		while (str[i] == c)
			i++;
		if (NULL == (split[row] = malloc(sizeof(char) *
									(split_len((str + i), c) + 1))))
		{
			free_all(split);
			return (NULL);
		}
		i = input_parts(split[row], str, split_len((str+i),c), i);
		row++;
	}
	split[array_size] = NULL;
	return (split);
}
