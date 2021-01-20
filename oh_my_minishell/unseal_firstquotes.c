/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unseal_firstquotes.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jikang <jikang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 01:14:27 by jikang            #+#    #+#             */
/*   Updated: 2021/01/21 01:38:30 by jikang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			check_firstquotes(char **splited, char *buff, t_var *v)
{
	if (splited[v->i][v->l] == '\'')
	{
		(v->l)++;
		while (splited[v->i][v->l] != '\0')
		{
			if (splited[v->i][v->l] == '\'' && (v->l)++)
				break ;
			buff[(v->k)++] = splited[v->i][v->l];
			(v->l)++;
		}
	}
	else if (splited[v->i][v->l] == '"')
	{
		(v->l)++;
		while (splited[v->i][v->l] != '\0')
		{
			if (splited[v->i][v->l] == '"' && (v->l)++)
				break ;
			buff[(v->k)++] = splited[v->i][v->l];
			(v->l)++;
		}
	}
	else
		return (1);
	return (0);
}

void		unseal_firstquotes(char **splited)
{
	t_var	v;
	char	buff[BUFF_MAX];

	v.i = 0;
	while (splited[v.i] != NULL)
	{
		v.l = 0;
		v.k = 0;
		init_array(buff);
		while (ft_is_whitespace(splited[v.i][v.l]))
			(v.l)++;
		if (check_firstquotes(splited, buff, &v) == 1)
		{
			(v.i)++;
			continue ;
		}
		while (splited[v.i][v.l] != '\0')
		{
			buff[(v.k)++] = splited[v.i][v.l];
			(v.l)++;
		}
		free(splited[v.i]);
		splited[v.i] = ft_strdup(buff);
		(v.i)++;
	}
}
