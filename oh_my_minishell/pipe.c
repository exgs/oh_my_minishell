/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunslee <yunslee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 00:30:26 by yunslee           #+#    #+#             */
/*   Updated: 2021/01/27 19:58:38 by yunslee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

static void	set_get_param(char *one_cmd)
{
	char **for_redirection;

	get_param()->cmd_trimed = ft_strtrim(one_cmd, " ");
	get_param()->cmd_splited = ft_split_minishell(get_param()->cmd_trimed, ' ');
	// for (size_t i = 0; get_param()->cmd_splited[i]; i++)
	// {
	// 	printf("%s\n", get_param()->cmd_splited[i]);
	// }
	get_param()->cmd_trimed = ft_strtrim(one_cmd, " ");
	parsing_redirect(get_param()->cmd_trimed);
	get_param()->cmd_splited = ft_split(g_buf, ' ');
	get_param()->cmd_redirect = splited_by_redirect(get_param()->cmd_splited,
												&get_param()->symbol_array);
}

int			execute_command_nopipe(char *one_cmd)
{
	int i;

	i = 0;
	set_get_param(one_cmd);
	while (get_param()->symbol_array[i] != 0)
	{
		if (get_param()->symbol_array[i] == -1)
		{
			g_status = 258 * 256;
			return (-1);
		}
		i++;
	}
	if (get_param()->symbol_array[0] == 0)
	{
		check_command(get_param()->cmd_splited[0], get_param()->cmd_splited,
															get_param()->envp);
		return (1);
	}
	else
	{
		if (-1 == execute_nopipe_redirect())
			return (-1);
	}
	return (1);
}

void		child_process(char **one_cmd_splited, int *fd)
{
	dup2(fd[1], 1);
	if (fd[0] != 0)
		close(fd[0]);
	if (fd[1] != 1)
		close(fd[1]);
	if (need_redirection() == ERROR)
		exit(1);
	else if (need_redirection() == TRUE)
	{
		execute_nopipe_redirect();
		exit(0);
	}
	check_command(one_cmd_splited[0], one_cmd_splited, get_param()->envp);
	exit(0);
}

void		parent_process(char **split_by_pipes, int *fd, int i)
{
	int	fd2[2];

	dup2(fd[0], 0);
	close(fd[0]);
	close(fd[1]);
	fd2[0] = 0;
	fd2[1] = 1;
	if (split_by_pipes[i + 1] != 0)
		pipe(fd2);
	execute_command_pipe(split_by_pipes, fd2, i);
}

int			execute_command_pipe(char **split_by_pipes, int *fd, int i)
{
	char	*one_cmd;
	pid_t	pid;

	one_cmd = split_by_pipes[i];
	set_get_param(one_cmd);
	pid = fork();
	if (pid == 0)
		child_process(get_param()->cmd_splited, fd);
	else
	{
		waitpid(pid, &g_status, 0);
		if (split_by_pipes[i + 1])
		{
			cmd_exit();
			parent_process(split_by_pipes, fd, i + 1);
		}
	}
	cmd_exit();
	return (1);
}
