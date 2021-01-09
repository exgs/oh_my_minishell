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

int		execve_nopipe(int num_cmd, char **argv, char *one_cmd_trimed)
{
	int pid;
	int i;

	if (num_cmd == LS)
	{
		if (-1 == (pid = fork()))
			return (-1);
		if (pid == 0)
		{
			execve("/bin/ls", argv, get_param()->envp);
		}
		else
		{
			waitpid(pid, &g_status, 0);
		}
	}
	/* 이번 시도에서는 문자열로 들어오는 one_cmd_trimed로 구현할 것임 */
	if (num_cmd == ECHO)
	{
		execute_echo(one_cmd_trimed);
	}
	if (num_cmd == CD) //built-in 함수를 써야함
	{
		execute_cd(argv[0], argv, get_param()->envp); // g_status 변수 세팅은 함수 안에서 해줘야할것같음 (?)
	}
	if (num_cmd == PWD)
	{
		execute_pwd();
	}
	if (num_cmd == EXPORT)
	{
		execute_export(argv[0], argv, get_param()->envp);
	}
	if (num_cmd == UNSET)
	{
		execute_unset(argv[0], argv, get_param()->envp);
	}
	if (num_cmd == ENV)
	{
		execute_env(argv[0], argv, get_param()->envp);
	}
	if (num_cmd == EXIT) //built-in 함수 써야함
		execute_exit(argv);
	if (num_cmd == GREP) // Grep을 단독으로 썼을 떄에 대해서는 따로 구별해야할 듯
	{
		if (-1 == (pid = fork()))
			return (-1);
		if (pid == 0)
		{
			execve("/usr/bin/grep", argv, get_param()->envp);
		}
		else
		{
			waitpid(pid, &g_status, 0);
		}
	}
	if (num_cmd == DQMARK) // $? 일 경우
	{
		/* zz 작업 중 zz*/
		ft_putstr_fd("bash: ", 1);
		ft_putnbr_fd(g_status / 256, 1);
		ft_putendl_fd(": command not found", 1);
	}
	return (1);
}

int		execute_command_nopipe(char *one_cmd)
{
	char *one_cmd_trimed;
	char **one_cmd_splited;
	int num_cmd;
	int temp;

	one_cmd_trimed = ft_strtrim(one_cmd, " ");
	one_cmd_splited = ft_split(one_cmd_trimed, ' ');
	// ft_putendl_fd("여기가 onecmdtrimed", 1);
	// ft_putendl_fd(one_cmd_trimed, 1);
	// ft_putendl_fd("----------------", 1);
	if (-1 == (num_cmd = which_command(one_cmd_splited[0])))
	{
		printf("command not found: %s\n", one_cmd_splited[0]);
		g_status = 127 * 256;
		return (-1);
	}
	temp = execve_nopipe(num_cmd, one_cmd_splited, one_cmd_trimed);
	if (temp == -1)
	{
		printf("fork error\n");
		g_status = 1 * 256;
		return (-1);
	}
	free_split(one_cmd_splited);
	free(one_cmd_trimed);
	return (1);
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
	if (-1 == (num_cmd = which_command(one_cmd_splited[0])))
	{
		printf("command not found: %s\n", one_cmd_splited[0]);
		return ;
	}
	path = which_command2(num_cmd);
	execve(path, one_cmd_splited, get_param()->envp);
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
	char *one_cmd_trimed;
	char **one_cmd_splited;
	int num_cmd;
	int temp;
	pid_t pid;

	one_cmd = split_by_pipes[i];
	one_cmd_trimed = ft_strtrim(one_cmd, " ");
	one_cmd_splited = ft_split(one_cmd_trimed, ' ');
	pid = fork();
	if (pid == 0)
		child_process(one_cmd_splited, fd);
	else
	{
		waitpid(pid, &g_status, 0);
		if (split_by_pipes[i+1])
			parent_process(split_by_pipes, fd, i+1);
	}
	free_split(one_cmd_splited);
	free(one_cmd_trimed);
	return (1);
}
