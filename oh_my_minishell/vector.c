/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykoh <ykoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 05:17:36 by ykoh              #+#    #+#             */
/*   Updated: 2021/01/21 05:17:37 by ykoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	vector_sort(char *arr[])
{
	int		i;
	int		j;
	int		size;
	char	*tmp;

	size = vector_size(arr);
	i = 0;
	while (i < size)
	{
		j = i + 1;
		while (j < size)
		{
			if (ft_strncmp(arr[i], arr[j], ft_strlen(arr[i]) + 1) > 0)
			{
				tmp = arr[i];
				arr[i] = arr[j];
				arr[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

int		vector_size(char *arr[])
{
	int	i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}

void	vector_clear(char *arr[])
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		arr[i] = NULL;
		i++;
	}
	free(arr);
	arr = NULL;
}

char	**vector_dup(char *arr[])
{
	char	**ret;
	int		size;
	int		i;

	size = vector_size(arr);
	if (!(ret = ft_calloc(size + 1, sizeof(char *))))
		return (NULL);
	i = 0;
	while (i < size)
	{
		ret[i] = ft_strdup(arr[i]);
		i++;
	}
	return (ret);
}

void	vector_push_back(char **arr[], char str[])
{
	char	**res;
	int		size;
	int		i;

	size = vector_size(*arr);
	if (!(res = ft_calloc(size + 2, sizeof(char *))))
		return ;
	i = 0;
	while (i < size)
	{
		res[i] = (*arr)[i];
		i++;
	}
	res[i] = ft_strdup(str);
	free(*arr);
	*arr = res;
}
