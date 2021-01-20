/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunslee <yunslee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 23:05:41 by yunslee           #+#    #+#             */
/*   Updated: 2021/01/21 00:06:40 by yunslee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int			is_same_file(char *path1, char *path2)
{
	struct stat	file1;
	struct stat	file2;

	if (stat(path1, &file1) == -1 || stat(path2, &file2) == -1)
		return (0);
	if (file1.st_dev != file2.st_dev || file1.st_ino != file2.st_ino ||
		file1.st_mode != file2.st_mode || file1.st_mode != file2.st_mode ||
		file1.st_nlink != file2.st_nlink || file1.st_uid != file2.st_uid ||
		file1.st_gid != file2.st_gid || file1.st_rdev != file2.st_rdev ||
		file1.st_size != file2.st_size ||
		file1.st_blksize != file2.st_blksize ||
		file1.st_blocks != file2.st_blocks ||
		file1.st_atime != file2.st_atime ||
		file1.st_mtime != file2.st_mtime || file1.st_ctime != file2.st_ctime)
		return (0);
	return (1);
}

static t_builtin	is_builtin(char command[])
{
	if (command == NULL)
		return (NULL);
	if (ft_strncmp(string_tolower(command), "echo", 5) == '\0')
		return (execute_echo);
	else if (ft_strncmp(string_tolower(command), "cd", 3) == '\0')
		return (execute_cd);
	else if (ft_strncmp(string_tolower(command), "pwd", 4) == '\0')
		return (execute_pwd);
	else if (ft_strncmp(string_tolower(command), "export", 7) == '\0')
		return (execute_export);
	else if (ft_strncmp(string_tolower(command), "unset", 6) == '\0')
		return (execute_unset);
	else if (ft_strncmp(string_tolower(command), "env", 4) == '\0')
		return (execute_env);
	else if (ft_strncmp(string_tolower(command), "exit", 5) == '\0')
		return (execute_exit);
	else if (ft_strncmp(string_tolower(command), "$", 1) == 0)
		return (execute_path);
	return (NULL);
}

static void			command_not_found(char *cmd)
{
	ft_putstr_fd("bash: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putendl_fd(": command not found", 2);
	g_status = 127 * 256;
}

void				check_command(char *cmd, char *argv[], char *envp[])
{
	t_builtin	f;
	char		*path;

	if (cmd == NULL)
		return ;
	if ((f = is_builtin(cmd)))
		f(cmd, argv, envp);
	else
	{
		if (!(path = get_path(cmd, argv, envp)))
		{
			command_not_found(cmd);
			return ;
		}
		if (is_same_file(path, "/usr/bin/env"))
			execute_env(path, argv, envp);
		else if (is_same_file(path, "/bin/echo"))
			execute_echo(path, argv, envp);
		else
			ft_execve(path, argv, envp);
		free(path);
	}
}
