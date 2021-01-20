/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refine_line_d.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jikang <jikang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 01:43:16 by jikang            #+#    #+#             */
/*   Updated: 2021/01/21 01:49:44 by jikang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** name : check_env
** aim : to convert string(temp) to environment variable
** original temp -> converted temp
** return (0)->found appropriate replacement
** return (1)->didnt find any replacement
*/

int			check_env(char *temp, char **envlist)
{
	int		i;
	int		j;
	char	*var;

	i = 0;
	while (envlist[i] != NULL)
	{
		if (ft_strncmp(envlist[i], temp, ft_strlen(temp) + 1) == '=')
		{
			ft_bzero(temp, ft_strlen(temp));
			var = ft_strchr(envlist[i], '=');
			var++;
			j = 0;
			while (*var != '\0')
			{
				temp[j] = *var;
				var++;
				j++;
			}
			return (0);
		}
		i++;
	}
	return (1);
}

int			replace_env(char *temp, char **envlist)
{
	int		i;
	int		j;

	if (temp[0] == 0)
	{
		temp[0] = '$';
		return (0);
	}
	if (ft_strncmp("?", temp, ft_strlen(temp) + 1) == 0)
	{
		temp[0] = '$';
		temp[1] = '?';
		return (0);
	}
	if (check_env(temp, envlist) == 0)
		return (0);
	return (1);
}
