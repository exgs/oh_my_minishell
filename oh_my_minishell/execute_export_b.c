/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_export_b.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykoh <ykoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 05:17:05 by ykoh              #+#    #+#             */
/*   Updated: 2021/01/21 05:17:06 by ykoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_envp(char **envp)
{
	const char	**tmp = (const char **)vector_dup(envp);
	char		*eq;
	int			i;

	vector_sort((char **)tmp);
	i = 0;
	while (tmp[i])
	{
		if (!(ft_strncmp(tmp[i], "_=", 2) == '\0'))
		{
			ft_putstr_fd("declare -x ", 1);
			if ((eq = ft_strchr(tmp[i], '=')))
			{
				write(1, tmp[i], eq - tmp[i] + 1);
				ft_putchar_fd('"', 1);
				write(1, eq + 1, ft_strlen(eq) - 1);
				ft_putchar_fd('"', 1);
			}
			else
				write(1, tmp[i], ft_strlen(tmp[i]));
			write(1, "\n", 1);
		}
		i++;
	}
	vector_clear((char **)tmp);
}
