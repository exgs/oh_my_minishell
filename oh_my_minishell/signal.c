/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jikang <jikang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 16:08:01 by jikang            #+#    #+#             */
/*   Updated: 2021/01/22 01:33:00 by jikang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	catch_sigint(int pid)
{
	(void)pid;
	pid = waitpid(-1, &g_status, WNOHANG);
	if (!pid)
	{
		g_flag[CTRL_C] = 130;
		g_status = 130 * 256;
	}
	else
	{
		g_flag[CTRL_C] = 1;
		g_status = 1 * 256;
	}
	ft_putstr_fd("\nminishell$ ", 2);
}

void	catch_sigquit(int pid)
{
	pid = waitpid(-1, &g_status, WNOHANG);
	if (!pid)
	{
		ft_putstr_fd("Quit: 3\n", 2);
		g_flag[CTRL_BS] = 130;
		g_status = 130 * 256;
	}
	else
	{
		g_flag[CTRL_BS] = 1;
		g_status = 1 * 256;
	}
}

void	catch_signals(void)
{
	signal(SIGINT, catch_sigint);
	signal(SIGQUIT, catch_sigquit);
}
