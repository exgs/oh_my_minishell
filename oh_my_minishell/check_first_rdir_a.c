/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_first_rdir_a.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jikang <jikang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 15:49:59 by jikang            #+#    #+#             */
/*   Updated: 2021/01/29 16:40:19 by jikang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int find_rdir(char *str, int i)
{
	if (str[i] == '>')
	{
		while (str[i] == ' ' || str[i] =='>')
			i++;
		while (str[i] != ' ' && str[i] && str[i] != '>')
		{
			i++;
			if (str[i] == '\0')
				return (-1);
		}
		while (str[i] == ' ')
			i++;
		return (find_rdir(str, i));
	}
	else
		return (i);
	return (i);
}

int find_next_rdir(char *str, int k)
{
	while (str[k] != '>' && str[k])
		k++;
	return (k);
}

char *insert_space(char **line, char *str)
{
	*line = ft_calloc(ft_strlen(str) + 2, sizeof(char));
	*line[0] = ' ';
	ft_memcpy(*line + 1, str, ft_strlen(str));

	return (*line);
}

char *conv_first_redir(char *str)
{
	char *line;
	t_var v;

	v.k = find_rdir(str, 0);
	v.l = find_next_rdir(str, v.k);
	if (v.k == -1)
		return (insert_space(&line, str));
	line = ft_calloc(ft_strlen(str) + 1, sizeof(char));
	v.i = 0;
	v.j = v.k;
	drag_redir_to_right_place(line, str, &v);

	return (line);
}

char *check_first_redir(char *str)
{
	char *line;

	line = conv_first_redir(str);
	free_swap(&str, line);
	line = NULL;
	return (str);
}
