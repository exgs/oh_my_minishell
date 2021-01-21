/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_execve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jikang <jikang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 15:37:31 by jikang            #+#    #+#             */
/*   Updated: 2021/01/21 15:37:57 by jikang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			is_execve(char *path, char **cmd_splited, char *envp[])
{
	int		num_cmd;
	pid_t	pid;

	num_cmd = which_command(cmd_splited[0]);
	if (num_cmd == LS || num_cmd == GREP || num_cmd == CLEAR || num_cmd == CAT)
	{
		if (-1 == (pid = fork()))
			return (-1);
		if (pid == 0)
		{
			execve(path, cmd_splited, get_param()->envp);
		}
		else
		{
			waitpid(pid, &g_status, 0);
		}
	}
	return (1);
	(void)envp;
}
