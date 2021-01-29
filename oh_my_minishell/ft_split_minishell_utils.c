/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_minishell_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunslee <yunslee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 04:43:22 by yunslee           #+#    #+#             */
/*   Updated: 2021/01/29 19:47:12 by yunslee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		index_one_two_split_len(const char *str, char c, char *flag_quotes)
{
	if (str[0] == '\0' || str[0] == c)
		return (0);
	else if (str[0] == '\'')
		*flag_quotes ^= 1;
	else if (str[0] == '\"')
		*flag_quotes ^= 2;
	if ((str[1] == '\0' || str[1] == c) &&
			(*flag_quotes ^ 0x1 && *flag_quotes ^ 0x2))
		return (1);
	else if (str[1] == '\'' && str[0] != '\\')
		*flag_quotes ^= 1;
	else if (str[1] == '\"' && str[0] != '\\')
		*flag_quotes ^= 2;
	return (SKIP);
}

int		index_one_two_size_array(const char *str, char c,
									char *flag_quotes, int *size)
{
	if (str[0] == '\0')
		return (*size);
	if (str[0] != c)
		*size += 1;
	if (str[0] == '\'')
		*flag_quotes ^= 1;
	if (str[0] == '\"')
		*flag_quotes ^= 2;
	if (str[1] == '\0')
		return (*size);
	else if (str[1] == c && str[2] != c)
	{
		if (str[2] != '\0')
			*size += 1;
	}
	if (str[1] == '\'' && str[0] != '\\')
		*flag_quotes ^= 1;
	if (str[1] == '\"' && str[0] != '\\')
		*flag_quotes ^= 2;
	if (str[1] != c && str[0] == c)
		*size += 1;
	return (SKIP);
}

void	change_flag_quotes(const char *str, int i, char *flag_quotes)
{
	if (str[i] == '\'')
		*flag_quotes ^= 1;
	if (str[i] == '\"')
		*flag_quotes ^= 2;
}
