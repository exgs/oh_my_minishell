/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunslee <yunslee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 22:32:36 by yunslee           #+#    #+#             */
/*   Updated: 2020/06/12 23:20:06 by yunslee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>

static int	atoi_while(const char *str, int i, int sign)
{
	unsigned long long int	sum;

	sum = 0;
	while (str[i] >= 48 && str[i] <= 57)
	{
		sum *= 10;
		sum += str[i] - 48;
		i++;
	}
	/*엄청 긴 숫자 text에 대해서 Overflow가 날 수 있어서 처리한 것이지만,
	LLONG_MIN에 대해서는 처리할 수 가 없다.*/
	if (sum > LLONG_MAX  && sign == -1) 
		return (0);
	if (sum > LLONG_MAX && sign == 1)
		return (-1);
	return ((int)sum);
}

int			ft_atoi(const char *str)
{
	int i;
	int sign;

	sign = 1;
	i = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13)) //space and whitespace 건너뛰기
		i++;
	if (str[i] == '-')
	{
		sign *= -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	if (!(str[i] >= 48 && str[i] <= 57))
		return (0);
	return (sign * atoi_while(str, i, sign));
}
