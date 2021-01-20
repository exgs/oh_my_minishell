/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunslee <yunslee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 02:18:08 by yunslee           #+#    #+#             */
/*   Updated: 2021/01/21 02:25:45 by yunslee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	minishell_exit(t_list *cmds)
{
	t_data *data;

	data = get_param();
	if (data->cmd_trimed != NULL)
		free(data->cmd_trimed);
	data->cmd_trimed = NULL;
	if (data->cmd_splited != NULL)
		free_split(data->cmd_splited);
	data->cmd_splited = NULL;
	if (data->cmd_redirect != NULL)
		free_3d_split(data->cmd_redirect);
	data->cmd_redirect = NULL;
	if (data->symbol_array != NULL)
		free(data->symbol_array);
	data->symbol_array = NULL;
	while (cmds != NULL)
	{
		if (cmds->split_by_pipes != NULL)
			vector_clear(cmds->split_by_pipes);
		cmds->split_by_pipes = NULL;
		cmds = cmds->next;
	}
	vector_clear(data->envp);
	close(g_dup_stdout);
	close(g_dup_stdin);
}

void	cmds_exit(t_list *cmds)
{
	t_data *data;

	data = get_param();
	if (data->cmd_trimed != NULL)
		free(data->cmd_trimed);
	data->cmd_trimed = NULL;
	if (data->cmd_splited != NULL)
		free_split(data->cmd_splited);
	data->cmd_splited = NULL;
	if (data->cmd_redirect != NULL)
		free_3d_split(data->cmd_redirect);
	data->cmd_redirect = NULL;
	if (data->symbol_array != NULL)
		free(data->symbol_array);
	data->symbol_array = NULL;
	while (cmds != NULL)
	{
		if (cmds->split_by_pipes != NULL)
			vector_clear(cmds->split_by_pipes);
		cmds->split_by_pipes = NULL;
		cmds = cmds->next;
	}
	ft_memset(get_param()->semi_arr, 0, sizeof(int) * 1000);
	ft_memset(g_except, 0, sizeof(int) * EX_END);
}

void	cmd_exit(void)
{
	t_data *data;

	data = get_param();
	if (data->cmd_trimed != NULL)
		free(data->cmd_trimed);
	data->cmd_trimed = NULL;
	if (data->cmd_splited != NULL)
		free_split(data->cmd_splited);
	data->cmd_splited = NULL;
	if (data->cmd_redirect != NULL)
		free_3d_split(data->cmd_redirect);
	data->cmd_redirect = NULL;
	if (data->symbol_array != NULL)
		free(data->symbol_array);
	data->symbol_array = NULL;
}
