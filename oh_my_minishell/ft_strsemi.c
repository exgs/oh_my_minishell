/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsemi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunslee <yunslee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 01:43:06 by yunslee           #+#    #+#             */
/*   Updated: 2021/01/21 01:57:31 by yunslee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	semicolon_indexs_notzero(char **line, int *semicolon_indexs, int i)
{
	int	temp;

	if (i == 0)
	{
		(*line)[semicolon_indexs[i]] = 0;
		(*line) += (semicolon_indexs[i] + 1);
	}
	else
	{
		temp = semicolon_indexs[i] - semicolon_indexs[i - 1] - 1;
		(*line)[temp] = 0;
		(*line) += (temp + 1);
	}
}

char		*ft_strsemi(char **line, int *semicolon_indexs, int i)
{
	int		size;
	char	*ret;

	if (**line == '\0')
		return (NULL);
	ret = *line;
	size = ft_strlen(*line);
	if (semicolon_indexs[i] == 0)
		*line += size;
	else
		semicolon_indexs_notzero(line, semicolon_indexs, i);
	return (ret);
}
