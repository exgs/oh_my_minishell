/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_command_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jikang <jikang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 23:15:10 by yunslee           #+#    #+#             */
/*   Updated: 2021/01/22 01:33:00 by jikang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char		*get_path_strjoin(char *cmd, char **arr)
{
	int			i;
	struct stat	buf;
	char		*path;
	char		*tmp;

	i = 0;
	while (arr[i])
	{
		tmp = ft_strjoin("/", cmd);
		path = ft_strjoin(arr[i], tmp);
		free(tmp);
		if (stat(path, &buf) == 0)
			break ;
		free(path);
		path = NULL;
		i++;
	}
	return (path);
}

char			*get_path(char *cmd, char *argv[], char *envp[])
{
	char		**arr;
	char		*path;

	while (*envp && ft_strncmp(*envp, "PATH", 5) != '=')
		envp++;
	if (ft_strchr(cmd, '/') || !*envp || !ft_strchr(*envp, '='))
		return (ft_strdup(cmd));
	arr = ft_split(ft_strchr(*envp, '=') + 1, ':');
	path = get_path_strjoin(cmd, arr);
	vector_clear(arr);
	return (path);
	(void)argv;
}

static void		change_g_status(void)
{
	if (g_flag[CTRL_D] != 0)
	{
		g_status = g_flag[CTRL_D] * 256;
	}
	else if (g_flag[CTRL_C] != 0)
	{
		g_status = g_flag[CTRL_C] * 256;
	}
	else if (g_flag[CTRL_BS] != 0)
	{
		g_status = g_flag[CTRL_BS] * 256;
	}
	return ;
}

static void		error_execve(const char *path, char *const argv[],
				char *const envp[], struct stat buf)
{
	if (stat(path, &buf) == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": ", 2);
		ft_putendl_fd(strerror(errno), 2);
		exit(127);
	}
	if ((buf.st_mode & S_IFMT) == S_IFDIR)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": ", 2);
		ft_putendl_fd(strerror(EISDIR), 2);
		exit(126);
	}
	if ((execve(path, argv, envp)) == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": ", 2);
		ft_putendl_fd(strerror(errno), 2);
		exit(126);
	}
}

void			ft_execve(const char *path, char *const argv[],
							char *const envp[])
{
	pid_t		pid;
	struct stat	buf;

	ft_bzero(&buf, sizeof(struct stat));
	if (-1 == (pid = fork()))
		return ;
	if (pid == 0)
	{
		error_execve(path, argv, envp, buf);
	}
	else
	{
		waitpid(pid, &g_status, 0);
		change_g_status();
	}
}
