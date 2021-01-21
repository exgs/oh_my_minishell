/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunslee <yunslee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 00:25:06 by yunslee           #+#    #+#             */
/*   Updated: 2021/01/21 17:20:56 by yunslee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_split(char **argv)
{
	int i;

	i = 0;
	if (argv == NULL)
		return ;
	while (argv[i] != NULL)
	{
		free(argv[i]);
		i++;
	}
	free(argv);
}

void	free_3d_split(char ***argv)
{
	int i;
	int j;

	i = 0;
	j = 0;
	if (argv == NULL)
		return ;
	while (argv[i] != NULL)
	{
		j = 0;
		while (argv[i][j] != NULL)
		{
			free(argv[i][j]);
			j++;
		}
		free(argv[i]);
		i++;
	}
	free(argv);
}
