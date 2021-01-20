/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_a.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jikang <jikang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 01:52:22 by jikang            #+#    #+#             */
/*   Updated: 2021/01/21 02:12:09 by jikang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_data				*get_param(void)
{
	static t_data	param;

	return (&param);
}

int					ft_is_whitespace(char c)
{
	return (c == ' ' || c == '\t' || c == '\v' || c == '\f'
			|| c == '\n' || c == '\r');
}

void				init_array(char *buff)
{
	int				n;

	n = 0;
	while (n < BUFF_MAX)
	{
		buff[n++] = 0;
	}
}

void				init_array_int(int *buff)
{
	int		n;

	n = 0;
	while (n < BUFF_MAX)
	{
		buff[n++] = 0;
	}
}

void				change_flag(int *flag)
{
	if (*flag == 0)
		*flag = 1;
	else if (*flag == 1)
		*flag = 0;
}
