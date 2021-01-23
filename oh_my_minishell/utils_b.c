/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_b.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunslee <yunslee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 01:51:44 by jikang            #+#    #+#             */
/*   Updated: 2021/01/23 12:54:40 by yunslee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** name : check_semicolon
** aim : check semicolon in string, to find valid semicolon
** ex) bash$ \; is not valid
** ex) bash$ ";" is not valid
** ex) bash$ ';' is not valid
*/

void		check_semicolon(char *str)
{
	t_var	v;
	char	buff[BUFF_MAX];

	init_value(buff, &v);
	init_array_int(get_param()->semi_arr);
	while (str[v.i] != '\0')
	{
		if (str[v.i] == '\'')
			change_flag(&(v.flag_sq));
		else if (str[v.i] == '"')
			change_flag(&(v.flag_bq));
		else if (str[v.i] == ';')
		{
			if (v.i >= 1 && str[v.i - 1] == '\\')
				buff[0] = 1;
			else if (v.flag_bq == 0 && v.flag_sq == 0)
			{
				get_param()->semi_arr[v.l] = v.i;
				(v.l)++;
			}
		}
		(v.i)++;
	}
}

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
** name : free_init
** aim : change string by free and get new string address
*/

void		free_init(char **data, char *init)
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
	v->k = 0;
	v->l = 0;
}
