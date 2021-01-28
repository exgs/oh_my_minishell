/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refine_line_b.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jikang <jikang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 01:40:53 by jikang            #+#    #+#             */
/*   Updated: 2021/01/28 20:40:05 by jikang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** name : back_slash
** aim : process back_slash with big quote option.
** @outside big quote, back slash is neglected. ex) bash$ \
** @inside big quote, ex) bash$ "\"", bash$ "\n"
*/

static void	back_slash(char *buff, char *line, t_var *v)
{
	if (v->flag_bq == 0 && line[(v->i) + 1] != '\0')
		(v->i)++;
	if (v->flag_bq == 1 && line[(v->i) + 1] == '"')
		(v->i)++;
	else if (v->flag_bq == 1 && line[(v->i) + 1] == '\\')
		(v->i)++;
	else if (line[(v->i) + 1] == '$')
		(v->i)++;
	buff[v->k] = line[v->i];
	(v->k)++;
}

void		skip_redirect(char *buff, char *line, t_var *v, char c)
{
	if (!ft_is_whitespace(line[v->i - 1]))
		buff[(v->k)++] = ' ';
	(v->i)++;
	if (line[v->i] == c)
		(v->i)++;
	while (ft_is_whitespace(line[v->i]))
		(v->i)++;
	while (!ft_is_whitespace(line[v->i]) && line[v->i])
		(v->i)++;
	while (ft_is_whitespace(line[v->i]))
		(v->i)++;
	(v->i)--;
}

/*
** name : is_redirect
** aim : ends string when meets "<", ">" without quote
** "<<", ">>" is ends also because of "<", ">"
** when meets "<", ">", push charector until meets null
*/

static int	is_redirect(char *buff, char *line, t_var *v)
{
	if (line[v->i] == '>' && v->flag_bq == 0)
	{
		skip_redirect(buff, line, v, '>');
		return (1);
	}
	else if (line[v->i] == '<' && v->flag_bq == 0)
	{
		skip_redirect(buff, line, v, '<');
		return (1);
	}
	return (0);
	(void)buff;
}

/*
** name : check_double_space
** aim : clear double_space without quotes
*/

static int	check_double_space(char *buff, char *line, t_var *v)
{
	buff[v->k] = line[v->i];
	(v->k)++;
	while (TRUE)
	{
		if (line[v->i] != ' ')
		{
			(v->i)--;
			return (0);
		}
		(v->i)++;
	}
	return (0);
}

/*
** name : refining_factory
** aim : process string outside of small quote.
** @big quote: there's difference when charector inside big quote and outside
** @back slash: there's difference when with back slash.
** @is_redirect: when valid redirect(>, <, >>, <<), string ends.
** 					it is for redirection
*/

int			refining_factory(char *buff, char *line, t_var *v, char **envlist)
{
	if (line[v->i] == '"')
		change_flag(&v->flag_bq);
	else if (line[v->i] == '$')
	{
		if (convert_env(buff, line, v, envlist) == 1)
			return (1);
	}
	else if (line[v->i] == '\\')
		back_slash(buff, line, v);
	else if (line[v->i] == ' ' && v->flag_bq == 0 && v->flag_sq == 0)
	{
		check_double_space(buff, line, v);
	}
	else
	{
		if (is_redirect(buff, line, v) == 1)
			return (0);
		buff[v->k] = line[v->i];
		(v->k)++;
	}
	return (0);
}
