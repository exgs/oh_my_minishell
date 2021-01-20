/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jikang <jikang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 23:35:17 by jikang            #+#    #+#             */
/*   Updated: 2021/01/21 01:35:46 by jikang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	split_str(char **new, char *str, int *buff, int pipe_num)
{
	int m;

	m = 0;
	while (m <= pipe_num)
	{
		if (m == 0)
			new[m] = ft_strdup_by_index(str, 0, buff[m] - 1);
		else
		{
			if (buff[m] == 0)
				buff[m] = ft_strlen(str) + 1;
			new[m] = ft_strdup_by_index(str, buff[m - 1] + 1, buff[m] - 1);
		}
		m++;
	}
	new[m] = NULL;
}

char		**split_str_by_pipe(char *str, int *buff, t_var *v)
{
	char	**new;
	int		pipe_num;

	pipe_num = v->k;
	new = (char **)malloc(sizeof(char *) * (pipe_num + 2));
	if (pipe_num == 0)
	{
		new[0] = ft_strdup(str);
		new[1] = NULL;
		return (new);
	}
	split_str(new, str, buff, pipe_num);
	return (new);
}

void		check_pipe(int *buff, char *substr, t_var *v)
{
	while (substr[v->i] != '\0')
	{
		if (substr[v->i] == '|')
		{
			if (v->flag_bq == 0 && v->flag_sq == 0 && v->flag_pipe == 0)
			{
				buff[(v->k)++] = v->i;
				v->flag_pipe = 1;
			}
		}
		else
		{
			if (substr[v->i] == '"')
				change_flag(&(v->flag_bq));
			else if (substr[v->i] == '\'')
				change_flag(&(v->flag_sq));
			v->flag_pipe = 0;
		}
		(v->i)++;
	}
}

/*
** name : split_pipe
** aim : split string by valid pipe
** @v : index, flag
** @vacant : nothing. it is for parameter
** @buff : get valid pipe in arr
*/

char		**split_pipe(char *substr)
{
	t_var	v;
	char	**str_arr;
	char	vacant[BUFF_MAX];
	int		buff[BUFF_MAX];

	init_value(vacant, &v);
	init_array_int(buff);
	check_pipe(buff, substr, &v);
	str_arr = split_str_by_pipe(substr, buff, &v);
	return (str_arr);
}
