/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunslee <yunslee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 01:25:54 by yunslee           #+#    #+#             */
/*   Updated: 2021/01/29 16:09:15 by yunslee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_redirect(char *str, t_index *index)
{
	int i;

	i = 0;
	if (str == NULL)
		return (-1);
	// while (str[i])
	// {
	// 	if (str[i] == '\'')
	// 		index->f_quote ^= 1;
	// 	if (str[i++] == '\"')
	// 		index->f_quote ^= 2;
	// }
	// if (index->f_quote & 1 || index->f_quote & 2)
	// 	return (FALSE);
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
	(void) index;
}

static int	redirect_num(char **one_cmd_splited, t_index *index)
{
	int i;
	int cnt;

	i = 0;
	cnt = 0;
	while (one_cmd_splited[i])
	{
		if (is_redirect(one_cmd_splited[i], index) != 0)
			cnt++;
		i++;
	}
	return (cnt);
}

void		splited_by_redirect_norm(char ***divid, char **split,
										char *symbol_array, t_index *index)
{
	char	*str;
	int		j;

	j = 0;
	while (split[index->i])
	{
		str = split[index->i];
		if (is_redirect(split[index->i], index) != 0)
		{
			input_symbol(split, symbol_array, index);
			divid[index->cnt] = malloc(sizeof(char *) *
									(index->i - index->before + 1));
			index->j = 0;
			while (index->before < index->i)
			{
				divid[index->cnt][index->j] = ft_strdup(split[index->before]);
				index->before++;
				index->j++;
			}
			divid[index->cnt][index->j] = NULL;
			index->before = index->i + 1;
			index->cnt++;
		}
		index->i++;
	}
}

char		***splited_by_redirect(char **one_cmd_splited, char **array)
{
	char	***divid;
	char	*symbol_array;
	char	*temp;
	int		p;
	t_index	index;

	s_index_bzero(&index);
	index.redir_num = redirect_num(one_cmd_splited, &index);
	divid = malloc(sizeof(char **) * (index.redir_num + 1 + 1));
	symbol_array = malloc(sizeof(char) * (index.redir_num + 1));
	splited_by_redirect_norm(divid, one_cmd_splited, symbol_array, &index);
	p = 0;
	divid[index.cnt] = malloc(sizeof(char *) * (index.i - index.before + 1));
	while (index.before < index.i)
	{
		temp = one_cmd_splited[index.before];
		divid[index.cnt][p++] = ft_strdup(one_cmd_splited[index.before]);
		index.before++;
	}
	divid[index.cnt][p] = NULL;
	divid[index.redir_num + 1] = NULL;
	symbol_array[index.redir_num] = 0;
	*array = symbol_array;
	return (divid);
}
