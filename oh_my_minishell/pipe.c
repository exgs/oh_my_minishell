#include "minishell.h"

char *string_tolower(char *str)
{
	int i;

	if (str == NULL)
		return (NULL);
	i = 0;
	while (str[i])
	{
		str[i] = ft_tolower(str[i]);
		i++;
	}
	return (str);
}

int		which_command(char *cmd)
{
	if (cmd == NULL)
		return (-1);
	if (!ft_strncmp(string_tolower(cmd),"echo",10))
		return (ECHO);
	if (!ft_strncmp(string_tolower(cmd),"cd",10))
		return (CD);
	if (!ft_strncmp(string_tolower(cmd),"pwd",10))
		return (PWD);
	if (!ft_strncmp(string_tolower(cmd),"export",10))
		return (EXPORT);
	if (!ft_strncmp(string_tolower(cmd),"unset",10))
		return (UNSET);
	if (!ft_strncmp(string_tolower(cmd),"env",10))
		return (ENV);
	if (!ft_strncmp(string_tolower(cmd),"exit",10))
		return (EXIT);
	if (!ft_strncmp(string_tolower(cmd),"ls",10))
		return (LS);
	if (!ft_strncmp(string_tolower(cmd),"grep",10))
		return (GREP);
	if (!ft_strncmp(string_tolower(cmd),"$?",10))
		return (DQMARK);
	if (!ft_strncmp(string_tolower(cmd),"clear",10))
		return (CLEAR);
	if (!ft_strncmp(string_tolower(cmd),"$?",10))
		return (DQMARK);
	else
		return (-1);
}

char	*which_command2(int num_cmd)
{
	if (num_cmd == -1)
		return ("/bin/ls");
	if (num_cmd == 0)
		return ("/bin/echo");
	if (num_cmd == 1)
		return ("/bin/cd");
	if (num_cmd == 2)
		return ("/bin/pwd");
	if (num_cmd == 3)
		return ("/bin/export");
	if (num_cmd == 4)
		return ("/bin/unset");
	if (num_cmd == 5)
		return ("/bin/env");
	if (num_cmd == 6)
		return ("/bin/exit");
	if (num_cmd == 7)
		return ("/bin/ls");
	if (num_cmd == 8)
		return ("/usr/bin/grep");
	else
		return 0;
}

int		execute_command_nopipe(char *one_cmd)
{
	int i = 0;

	get_param()->cmd_trimed = ft_strtrim(one_cmd, " ");
	parsing_redirect(get_param()->cmd_trimed);
	get_param()->cmd_splited = ft_split(g_buf, ' ');
	get_param()->cmd_redirect = splited_by_redirect(get_param()->cmd_splited,
												&get_param()->symbol_array);
	// print_3d_split(get_param()->cmd_redirect);
	// for (size_t i = 0; get_param()->symbol_array[i] != 0; i++)
	// {
	// 	printf("%d|", get_param()->symbol_array[i]);
	// }
	// printf("\n");
	while (get_param()->symbol_array[i] != 0)
	{
		if (get_param()->symbol_array[i] == -1)
			return (-1);
		i++;
	}
	if (get_param()->symbol_array[0] == 0)
	{
		check_command(get_param()->cmd_splited, get_param()->envp);
		return (1);
	}
	else
	{
		if (-1 == execute_nopipe_redirect())
			return (-1);
	}
	return (1);
}

int need_redirection()
{
	int i;

	i = 0;
	while (get_param()->symbol_array[i] != 0)
	{
		if (get_param()->symbol_array[i] == -1)
			return (ERROR);
		i++;
	}
	if (get_param()->symbol_array[0] == 0)
	{
		return (FALSE);
	}
	else
	{
		return (TRUE);
	}
}

void	child_process(char **one_cmd_splited, int *fd)
{
	int	i;
	int num_cmd;
	int temp;
	char *path;

	dup2(fd[1], 1);
	if (fd[0] != 0)
		close(fd[0]);
	if (fd[1] != 1)
		close(fd[1]);
	if (need_redirection() == ERROR)
		exit(0);
	else if (need_redirection() == TRUE)
	{
		execute_nopipe_redirect();
		exit(0);
	}
	check_command(one_cmd_splited, get_param()->envp);
	exit(0);
}

void	parent_process(char **split_by_pipes, int *fd, int i)
{
	int		fd2[2];

	dup2(fd[0], 0); //표준입력으로 child process에서 써줬던 것을 읽겠다.
	close(fd[0]);
	close(fd[1]);
	fd2[0] = 0;
	fd2[1] = 1;
	if (split_by_pipes[i + 1] != 0)
		pipe(fd2);
	execute_command_pipe(split_by_pipes, fd2, i);
}

int		execute_command_pipe(char **split_by_pipes, int *fd, int i)
{
	char *one_cmd;
	int num_cmd;
	pid_t pid;

	one_cmd = split_by_pipes[i];
	get_param()->cmd_trimed = ft_strtrim(one_cmd, " ");
	parsing_redirect(get_param()->cmd_trimed);
 	get_param()->cmd_splited = ft_split(g_buf, ' ');
	get_param()->cmd_redirect = splited_by_redirect(get_param()->cmd_splited,
											&get_param()->symbol_array);
	pid = fork();
	if (pid == 0)
	{
		child_process(get_param()->cmd_splited, fd);
	}
	else
	{
		waitpid(pid, &g_status, 0);
		if (split_by_pipes[i+1])
		{
			cmd_exit();
			parent_process(split_by_pipes, fd, i+1);
		}
	}
	cmd_exit();
	return (1);
}
