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

static char	get_prev_char(char *str, int i)
{
	i--;
	while (i >= 0)
	{
		if (!ft_is_whitespace(str[i]))
			return (str[i]);
		i--;
	}
	return ('\0');
}

static char	get_next_char(char *str)
{
	int i;

	str++;
	i = 0;
	while (str[i])
	{
		if (!ft_is_whitespace(str[i]))
			return (str[i]);
		i++;
	}
	return (str[i]);
}

/*
** name : check_semicolon
** aim : check semicolon in string, to find valid semicolon
** ex) bash$ \; is not valid
** ex) bash$ ";" is not valid
** ex) bash$ ';' is not valid
*/

int			check_semicolon(char *str)
{
	t_var	v;
	char	next;
	char	prev;

	ft_bzero(&v, sizeof(t_var));
	init_array_int(get_param()->semi_arr);
	while (str[v.i] != '\0')
	{
		if (str[v.i] == '\'')
			change_flag(&(v.flag_sq));
		else if (str[v.i] == '"')
			change_flag(&(v.flag_bq));
		else if ((v.flag_bq == 0 && v.flag_sq == 0) && (str[v.i] == '>' || str[v.i] == '<'))
		{
			if (!(v.i >= 1 && str[v.i - 1] == '\\'))
			{
				next = get_next_char(str + v.i);
				if (next == '\0' || next == ';')
					return (msg_syntax("minishell", '>', 258));
			}
		}
		else if ((v.flag_bq == 0 && v.flag_sq == 0) && str[v.i] == '|')
		{
			if (!(v.i >= 1 && str[v.i - 1] == '\\'))
			{
				prev = get_prev_char(str, v.i);
				next = get_next_char(str + v.i);
				if (prev == '\0' || prev == ';' || next == '\0' || next == ';')
					return (msg_syntax("minishell", '|', 258));
			}
		}
		else if ((v.flag_bq == 0 && v.flag_sq == 0) && str[v.i] == ';')
		{
			if (!(v.i >= 1 && str[v.i - 1] == '\\'))
			{
				prev = get_prev_char(str, v.i);
				if (prev == '\0' || prev == ';')
					return (msg_syntax("minishell", ';', 258));			
				get_param()->semi_arr[v.l++] = v.i;
			}
		}
		(v.i)++;
	}
	return (0);
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
