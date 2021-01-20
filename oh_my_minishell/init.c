/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunslee <yunslee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 02:17:36 by yunslee           #+#    #+#             */
/*   Updated: 2021/01/21 02:24:02 by yunslee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	dup_initalize(void)
{
	dup2(g_dup_stdin, STDIN_FILENO);
	dup2(g_dup_stdout, STDOUT_FILENO);
}

void	minishell_init(int argc, char **argv, char **envp)
{
	ft_memset(g_flag, 0, sizeof(int) * F_END);
	ft_memset(g_buf, 0, sizeof(char) * 1000);
	ft_memset(get_param()->semi_arr, 0, sizeof(int) * 1000);
	ft_memset(g_except, 0, sizeof(char) * EX_END);
	g_dup_stdin = dup(STDIN_FILENO);
	g_dup_stdout = dup(STDOUT_FILENO);
	get_param()->cmd_trimed = NULL;
	get_param()->cmd_splited = NULL;
	get_param()->cmd_redirect = NULL;
	get_param()->symbol_array = NULL;
	get_param()->envp = vector_dup(envp);
	init_array_int(get_param()->semi_arr);
	catch_signals();
}
