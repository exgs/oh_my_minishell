/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jikang <jikang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 15:17:21 by jikang            #+#    #+#             */
/*   Updated: 2021/01/25 14:53:11 by jikang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	error_except(void)
{
	if (g_except[SYNTAX] != 0)
	{
		g_status = 258 * 256;
		ft_putstr_fd("minishell: syntax error near unexpected token '", 2);
		if (g_except[SYNTAX] == 10)
			ft_putstr_fd("newline", 2);
		else
			ft_putchar_fd(g_except[SYNTAX], 2);
		ft_putstr_fd("'\n", 2);
	}
	g_except[SYNTAX] = 0;
}

static int	check_delimeter(char **str)
{
	if (g_except[SYNTAX] == '|')
		return (-1);
	if (str[0] == NULL)
	{
		g_except[SYNTAX] = '|';
		return (-1);
	}
	if (ft_strncmp(str[0], ";", 1) == 0)
	{
		g_except[SYNTAX] = ';';
		return (-1);
	}
	if (ft_strncmp(str[0], "<", 1) == 0)
	{
		g_except[SYNTAX] = 10;
		return (-1);
	}
	if (ft_strncmp(str[0], ">", 1) == 0)
	{
		g_except[SYNTAX] = 10;
		return (-1);
	}
	return (0);
}

int			execute_command(char **split_by_pipes)
{
	int		fd[2];

	if (-1 == check_delimeter(split_by_pipes))
		return (-1);
	if (split_by_pipes[1] == NULL)
	{
		if (-1 == (execute_command_nopipe(split_by_pipes[0])))
		{
			ft_putstr_fd("minishell : syntax error near unexpected token\n", 2);
			return (-1);
		}
		return (1);
	}
	pipe(fd);
	execute_command_pipe(split_by_pipes, fd, 0);
	dup2(g_dup_stdin, STDIN_FILENO);
	cmd_exit();
	return (1);
}

int			execute_multi_commands(t_list *cmds)
{
	t_list	*cur;

	cur = cmds;
	while (cur != NULL)
	{
		if (-1 == execute_command(cur->split_by_pipes))
			error_except();
		cmd_exit();
		cur = cur->next;
	}
	cmds_exit(cmds);
	return (1);
}
