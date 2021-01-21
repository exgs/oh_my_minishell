/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunslee <yunslee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 03:40:40 by yunslee           #+#    #+#             */
/*   Updated: 2021/01/21 17:05:31 by yunslee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_redirect(char *str, t_index *index)
{
	int i;

	i = 0;
	if (str == NULL)
		return (-1);
	while (str[i])
	{
		if (str[i] == '\'')
			index->f_quote ^= 1;
		if (str[i++] == '\"')
			index->f_quote ^= 2;
	}
	if (index->f_quote & 1 || index->f_quote & 2)
		return (FALSE);
	if (str[0] == '>' || str[0] == '<')
	{
		if (!ft_strncmp(str, ">>", 3))
			return (D_RIGHT);
		else if (!ft_strncmp(str, ">", 2))
			return (RIGHT);
		else if (!ft_strncmp(str, "<", 2))
			return (LEFT);
		return (ERROR);
	}
	return (FALSE);
}

void		input_symbol(char **split, char *symbol_array, t_index *index)
{
	if (is_redirect(split[index->i], index) == LEFT)
		symbol_array[index->z++] = LEFT;
	else if (is_redirect(split[index->i], index) == RIGHT)
		symbol_array[index->z++] = RIGHT;
	else if (is_redirect(split[index->i], index) == D_RIGHT)
		symbol_array[index->z++] = D_RIGHT;
	else
		symbol_array[index->z++] = ERROR;
}

int			parsing_redirect(char *str)
{
	int	i;
	int	k;

	ft_memset(g_buf, 0, 1000);
	i = 0;
	k = 0;
	while (str[i] != '\0')
	{
		g_buf[k++] = str[i];
		if ((str[i] == '<' || str[i] == '>') &&
				(str[i + 1] == '<' || str[i + 1] == '>'))
		{
			i++;
			continue;
		}
		else if ((str[i] == '<' || str[i] == '>') &&
					(str[i + 1] != '>' && str[i + 1] != '<'))
			g_buf[k++] = ' ';
		else if ((str[i] != '<' && str[i] != '>') &&
					(str[i + 1] == '>' || str[i + 1] == '<'))
			g_buf[k++] = ' ';
		i++;
	}
	return (1);
}

void		s_index_bzero(t_index *index)
{
	index->before = 0;
	index->cnt = 0;
	index->i = 0;
	index->j = 0;
	index->redir_num = 0;
	index->z = 0;
	index->f_quote = 0;
}
