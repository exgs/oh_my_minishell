/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunslee <yunslee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 16:09:48 by yunslee           #+#    #+#             */
/*   Updated: 2020/04/13 23:03:32 by yunslee          ###   ########.fr       */
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

void				ft_putendl_fd(char *s, int fd)
{
	if (s == 0)
		return ((void)0);
	write(fd, s, ft_strlen(s));
	write(fd, "\n", 1);
}
