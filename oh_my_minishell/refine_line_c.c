/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refine_line_c.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jikang <jikang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 01:47:13 by jikang            #+#    #+#             */
/*   Updated: 2021/01/21 01:47:55 by jikang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		take_buff(char *buff, char *temp, int *k)
{
	int		j;

	j = 0;
	while (temp[j] != '\0')
	{
		buff[*k] = temp[j];
		(*k)++;
		j++;
	}
}

/*
** name : back_slash
** aim : process back_slash with big quote option.
** @outside big quote, back slash is neglected. ex) bash$ \
** @inside big quote, ex) bash$ "\"", bash$ "\n"
*/

void		insert_dq_in_str(char *str, t_var *v)
{
	int		exit_status;

	exit_status = g_status / 256;
	if (exit_status > 100)
	{
		str[(v->k)++] = exit_status / 100 + 48;
		str[(v->k)++] = (exit_status % 100) / 10 + 48;
		str[(v->k)++] = exit_status % 10 + 48;
	}
	else if (exit_status > 10)
	{
		str[(v->k)++] = exit_status / 10 + 48;
		str[(v->k)++] = exit_status % 10 + 48;
	}
	else
	{
		str[(v->k)++] = exit_status + 48;
	}
}

static int	is_env_ch(char c)
{
	if (ft_isalpha(c) || ft_isdigit(c) || c == '_')
		return (1);
	return (0);
}

int			dollor_qmark(char *buff, char *line, t_var *v)
{
	if (line[v->i] == '$')
	{
		buff[(v->k)++] = '$';
		buff[(v->k)++] = '$';
		return (0);
	}
	else if (line[v->i] == '?')
	{
		insert_dq_in_str(buff, v);
		return (0);
	}
	return (1);
}

/*
** name : convert_env
** aim : when dollar exists, it converts to appropriate string.
** 1. insert $string in temp, 2. convert temp into env variable,
** 3. take converted temp into buff.
** ex) $$, $?, $PWD, $unknown
*/

int			convert_env(char *buff, char *line, t_var *v, char **envlist)
{
	int		j;
	char	temp[BUFF_MAX];

	init_array(temp);
	(v->i)++;
	if (dollor_qmark(buff, line, v) == 0)
		return (0);
	j = 0;
	while (is_env_ch(line[v->i]))
	{
		temp[j] = line[v->i];
		(v->i)++;
		j++;
	}
	(v->i)--;
	if (replace_env(temp, envlist) == 1)
	{
		ft_putendl_fd("Environment variable error", 2);
		g_status = 1 * 256;
		return (1);
	}
	take_buff(buff, temp, &v->k);
	return (0);
}
