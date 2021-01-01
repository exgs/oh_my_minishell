/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunslee <yunslee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 16:07:30 by yunslee           #+#    #+#             */
/*   Updated: 2020/04/13 23:04:10 by yunslee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

static unsigned int	ft_strlen(const char *s)
{
	unsigned int i;

	i = 0;
	while (s[i])
	{
		i++;
	}
	return (i);
}

void				ft_putstr_fd(char *s, int fd)
{
	if (s == 0)
		return ((void)0);
	write(fd, s, ft_strlen(s));
}
