/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refine_line_b.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jikang <jikang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 01:40:53 by jikang            #+#    #+#             */
/*   Updated: 2021/01/21 01:41:53 by jikang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** name : back_slash
** aim : process back_slash with big quote option.
** @outside big quote, back slash is neglected. ex) bash$ \
** @inside big quote, ex) bash$ "\"", bash$ "\n"
*/

void	back_slash(char *buff, char *line, t_var *v)
{
	if (v->flag_bq == 0)
		(v->i)++;
	else if (v->flag_bq == 1 && line[(v->i) + 1] == '"')
		(v->i)++;
	buff[v->k] = line[v->i];
	(v->k)++;
}

/*
** name : is_redirect
** aim : ends string when meets "<", ">" without quote
** "<<", ">>" is ends also because of "<", ">"
** when meets "<", ">", push charector until meets null
*/

int		is_redirect(char *buff, char *line, t_var *v)
{
	if (line[v->i] == '>' && v->flag_bq == 0)
	{
		while (line[v->i] != '\0')
			(v->i)++;
		(v->i)--;
		return (1);
	}
	else if (line[v->i] == '<' && v->flag_bq == 0)
	{
		while (line[v->i] != '\0')
			(v->i)++;
		(v->i)--;
		return (1);
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

int		refining_factory(char *buff, char *line, t_var *v, char **envlist)
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
	else
	{
		if (is_redirect(buff, line, v) == 1)
			return (0);
		buff[v->k] = line[v->i];
		(v->k)++;
	}
	return (0);
}
