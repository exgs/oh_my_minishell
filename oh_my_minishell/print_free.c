/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunslee <yunslee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 00:25:06 by yunslee           #+#    #+#             */
/*   Updated: 2021/01/21 00:25:52 by yunslee          ###   ########.fr       */
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

void	print_split(char **split)
{
	int i;

	i = 0;
	if (split == NULL)
		return ;
	while (split[i])
	{
		printf("split|%d번째:%s\n", i, split[i]);
		i++;
	}
}

void	print_cmd_list(t_list *cmd)
{
	int i;
	int lst_length;

	i = 0;
	lst_length = ft_lstsize(cmd);
	while (i < lst_length)
	{
		printf("linked|%d번째:%s\n", i, cmd->content);
		cmd = cmd->next;
		i++;
	}
}

void	print_3d_split(char ***argv)
{
	int		i;
	int		j;

	i = 0;
	if (argv == NULL)
		return ;
	printf("=======================\n");
	while (argv[i] != NULL)
	{
		j = 0;
		while (argv[i][j])
		{
			printf("%s\n", argv[i][j]);
			j++;
		}
		printf("-----------------\n");
		i++;
	}
	printf("=======================\n");
}
