/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_first_rdir_b.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jikang <jikang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 15:49:59 by jikang            #+#    #+#             */
/*   Updated: 2021/01/29 15:57:04 by jikang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	drag_redir_to_right_place(char *line, char *str, t_var *v)
{
	while (str[v->j] != '\0' && v->j < v->l)
	{
		line[v->i] = str[v->j];
		v->i++;
		v->j++;
	}
	v->j = 0;
	while (v->j < v->k)
	{
		line[v->i] = str[v->j];
		v->i++;
		v->j++;
	}
	while (str[v->l])
	{
		line[v->i] = str[v->l];
		v->i++;
		v->l++;
	}
	line[v->i] = '\0';
}
