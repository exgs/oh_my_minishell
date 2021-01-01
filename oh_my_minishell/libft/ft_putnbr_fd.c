/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunslee <yunslee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 16:11:44 by yunslee           #+#    #+#             */
/*   Updated: 2020/04/10 02:54:04 by yunslee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int	nbr;
	char			mod;

	if (n < 0)
	{
		nbr = (unsigned int)(n * -1);
		write(fd, "-", 1);
	}
	else
		nbr = (unsigned int)(n);
	if (nbr < 10)
	{
		mod = (char)(nbr % 10) + '0';
		write(fd, &mod, 1);
	}
	else
	{
		mod = (char)(nbr % 10) + '0';
		nbr /= 10;
		ft_putnbr_fd(nbr, fd);
		write(fd, &mod, 1);
	}
}
