/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_b.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jikang <jikang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 01:51:44 by jikang            #+#    #+#             */
/*   Updated: 2021/01/29 16:43:27 by jikang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** name : ft_strdup_by_index
** aim : duplicate string by index
*/

char		*ft_strdup_by_index(char *str, int start, int end)
{
	char	*new;
	int		i;
	int		j;

	if (str == NULL || start < 0 || start > end || ft_strlen(str) < end)
		return (0);
	new = malloc(sizeof(char) * (end - start + 2));
	i = start;
	j = 0;
	while (i <= end)
	{
		new[j] = str[i];
		i++;
		j++;
	}
	new[j] = '\0';
	return (new);
}

/*
** name : free_swap
** aim : change string by free and get new string address
*/

void		free_swap(char **data, char *init)
{
	free(*data);
	*data = init;
}

/*
** name : init_value
** aim : initialize variables
** @i is for line index
** @k is for buff index(buff is for return string)
** @l is for valid pipe index which is for divide string
*/

void		init_value(char *buff, t_var *v)
{
	init_array(buff);
	v->flag_bq = 0;
	v->flag_sq = 0;
	v->flag_backslash = 0;
	v->flag_pipe = 0;
	v->i = 0;
	v->j = 0;
	v->k = 0;
	v->l = 0;
}
