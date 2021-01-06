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

int which_command(char *cmd)
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
	else
		return (-1);
}

int execve_rw_endofpipe(int num_cmd, char **argv, char *one_cmd_trimed, t_setting *setting)
{
	int pid;
	int *pipe_fd;
	int i;

	pipe_fd = setting->pipe_fd;

	if (num_cmd == GREP) // Grep을 단독으로 썼을 떄에 대해서는 따로 구별해야할 듯
	{
		if (-1 == (pid = fork()))
			return (-1);
		if (pid == 0)
		{
			int temp;
			close(pipe_fd[WRITE]);
			temp = dup2(pipe_fd[READ], STDIN_FILENO);
			execve("/usr/bin/grep", argv, setting->envp);
		}
		else
		{
			close(pipe_fd[READ]);
			wait(NULL);
		}
	}
	return (1);
}

int execve_w_endofpipe(int num_cmd, char **argv, char *one_cmd_trimed, t_setting *setting)
{
	int pid;
	int *pipe_fd;
	int i;

	pipe_fd = setting->pipe_fd;
	if (num_cmd == LS)
	{
		if (-1 == (pid = fork()))
			return (-1);
		if (pid == 0)
		{
			execve("/bin/ls", argv, setting->envp);
		}
		else
		{
			wait(NULL);
		}
	}
	/* 이번 시도에서는 문자열로 들어오는 one_cmd_trimed로 구현할 것임 */
	if (num_cmd == ECHO)
	{
		execute_echo(one_cmd_trimed);
	}
	if (num_cmd == CD) //built-in 함수를 써야함
	{
		// printf("CD command\n");
		int buf[100];
		chdir(argv[1]);
		// getcwd(buf,100);
	}
	if (num_cmd == PWD)
	{
		execute_pwd();
	}
	if (num_cmd == EXPORT)
	{
		if (-1 == (pid = fork()))
			return (-1);
		if (pid == 0)
			execve("/bin/sh", argv, setting->envp);
		else
		{
			wait(NULL);
		}
	}
	if (num_cmd == UNSET)
	{
		if (-1 == (pid = fork()))
			return (-1);
		if (pid == 0)
			execve("/bin/sh", argv, setting->envp);
		else
		{
			wait(NULL);
		}
	}
	if (num_cmd == ENV)
	{
		if (-1 == (pid = fork()))
			return (-1);
		if (pid == 0)
			execve("/usr/bin/env", argv, setting->envp);
		else
		{
			wait(NULL);
		}
	}
	if (num_cmd == EXIT) //built-in 함수 써야함
		execute_exit(argv);
	return (1);
}

int flush_pipe_fd(t_setting *setting)
{
	// printf("1:%d\n", setting->pipe_fd[READ]);
	// printf("2:%d\n", setting->pipe_fd[WRITE]);
	close(setting->pipe_fd[READ]);
	close(setting->pipe_fd[WRITE]);
	if (-1 == pipe(setting->pipe_fd))
	{
		printf("pipe error\n");
		return (-1);
	}
	// printf("1:%d\n", setting->pipe_fd[READ]);
	// printf("2:%d\n", setting->pipe_fd[WRITE]);
	return (1);
}
int	execve_rw_pipe(int num_cmd, char **argv, t_setting *setting)
{
	int pid;
	int *pipe_fd;
	int *pipe_fd2;
	int dup_stdout;

	dup_stdout = dup(STDOUT_FILENO);
	pipe_fd = setting->pipe_fd;
	pipe_fd2 = setting->pipe_fd2;
	if (num_cmd == GREP)
	{
		if (-1 == (pid = fork()))
			return (-1);
		if (pid == 0)
		{
			int pipe_child[2];
			int pid2;
			pipe(pipe_child);
			// dup2(pipe_fd[WRITE], STDOUT_FILENO);
			dup2(pipe_fd[1],pipe_child[1]);
			pid2 = fork();
			if (pid2 == 0)
			{
				close(pipe_fd[WRITE]);
				close(pipe_child[READ]);
				dup2(pipe_fd[READ], STDIN_FILENO);
				dup2(pipe_child[WRITE], STDOUT_FILENO);
				execve("/usr/bin/grep", argv, setting->envp);
			}
			close(pipe_child[WRITE]);
			close(pipe_fd[READ]);
			wait(NULL);
			exit(0);

			// dup2(pipe_fd2[READ], STDIN_FILENO);
			// close(pipe_fd2[WRTIE]);
			// execve("/usr/bin/grep", argv, setting->envp);
		}
		else
		{
			// close(pipe_fd2[READ]);
			close(pipe_fd[WRITE]);
			wait(NULL);
		}
	}
	return (1);
}
int	execve_w_pipe(int num_cmd, char **argv, t_setting *setting)
{
	int pid;
	int *pipe_fd;

	pipe_fd = setting->pipe_fd;
	if (num_cmd == LS)
	{
		if (-1 == (pid = fork()))
			return (-1);
		if (pid == 0)
		{
			close(pipe_fd[READ]);
			dup2(pipe_fd[WRITE], STDOUT_FILENO);
			execve("/bin/ls", argv, setting->envp);
		}
		else
		{
			close(pipe_fd[WRITE]);
			wait(NULL);
		}
	}
	if (num_cmd == ECHO)
	{
		if (-1 == (pid = fork()))
			return (-1);
		if (pid == 0)
		{
			close(pipe_fd[READ]);
			dup2(pipe_fd[WRITE], STDOUT_FILENO);
			execve("/bin/echo", argv, setting->envp);
		}
		else
		{
			close(pipe_fd[WRITE]);
			wait(NULL);
		}
	}
	if (num_cmd == CD) //built-in 함수를 써야함
	{
		int buf[100];
		chdir(argv[1]);
		// getcwd(buf,100);
	}
	if (num_cmd == PWD)
	{
		if (-1 == (pid = fork()))
			return (-1);
		if (pid == 0)
		{
			close(pipe_fd[READ]);
			dup2(pipe_fd[WRITE], STDOUT_FILENO);
			execve("/bin/pwd", argv, setting->envp);
		}
		else
		{
			close(pipe_fd[WRITE]);
			wait(NULL);
		}
	}
	if (num_cmd == EXPORT)
	{
		if (-1 == (pid = fork()))
			return (-1);
		if (pid == 0)
		{
			close(pipe_fd[READ]);
			dup2(pipe_fd[WRITE], STDOUT_FILENO);
			execve("/bin/sh", argv, setting->envp);
		}
		else
		{
			close(pipe_fd[WRITE]);
			wait(NULL);
		}
	}
	if (num_cmd == UNSET)
	{
		if (-1 == (pid = fork()))
			return (-1);
		if (pid == 0)
		{
			close(pipe_fd[READ]);
			dup2(pipe_fd[WRITE], STDOUT_FILENO);
			execve("/bin/sh", argv, setting->envp);
		}
		else
		{
			close(pipe_fd[WRTIE]);
			wait(NULL);
		}
	}
	if (num_cmd == ENV)
	{
		if (-1 == (pid = fork()))
			return (-1);
		if (pid == 0)
		{
			close(pipe_fd[READ]);
			dup2(pipe_fd[WRITE], STDOUT_FILENO);
			execve("/usr/bin/env", argv, setting->envp);
		}
		else
		{
			close(pipe_fd[WRTIE]);
			wait(NULL);
		}
	}
	if (num_cmd == EXIT) //built-in 함수 써야함
		exit(0);
	return (1);
}
int which_typeof_command(int num_cmd)
{
	int n = num_cmd;
	if (n == ECHO || n == CD || n == PWD || n == EXPORT || n == UNSET ||
				n == ENV || n == EXIT || n == LS)
		return (WRONLY);
	else if (n == GREP)
		return (RDWR);
	else
		return (-1);
}

int passing_to_stdout(char **one_cmd_splited, char *one_cmd_trimed, t_setting *setting)
{
	int num_cmd;
	int temp;

	if (-1 == (num_cmd = which_command(one_cmd_splited[0])))
	{
		printf("command not found: %s\n", one_cmd_splited[0]);
		return (-1);
	}

	if (which_typeof_command(num_cmd) == WRONLY)
	{
		if (-1 == flush_pipe_fd(setting))
			return (-1);
		temp = execve_w_endofpipe(num_cmd, one_cmd_splited, one_cmd_trimed, setting);
	}
	else if (which_typeof_command(num_cmd) == RDWR)
	{
		temp = execve_rw_endofpipe(num_cmd, one_cmd_splited, one_cmd_trimed, setting);
	}
	if (temp == -1)
	{
		printf("fork error\n");
		return (-1);
	}
	return (1);
}

int passing_to_pipe(char **one_cmd_splited, t_setting *setting)
{
	int num_cmd;
	int temp;

	if (-1 == (num_cmd = which_command(one_cmd_splited[0])))
	{
		printf("command not found: %s\n", one_cmd_splited[0]);
		return (-1);
	}
	if (which_typeof_command(num_cmd) == WRONLY)
	{
		if (-1 == flush_pipe_fd(setting))
			return (-1);
		temp = execve_w_pipe(num_cmd, one_cmd_splited, setting);
	}
	else if (which_typeof_command(num_cmd) == RDWR)
	{
		temp = execve_rw_pipe(num_cmd, one_cmd_splited, setting);
	}

	if (temp == -1)
	{
		printf("fork error\n");
		return (-1);
	}
	return (1);
}

int execute_command(char **split_by_pipes, t_setting *setting)
{
	char *one_cmd;
	char *one_cmd_trimed;
	char **one_cmd_splited;
	int i = 0;

	if (-1 == pipe(setting->pipe_fd))
	{
		printf("pipe error\n");
		return (-1);
	}
	while (split_by_pipes[i])
	{
		one_cmd = split_by_pipes[i];
		one_cmd_trimed = ft_strtrim(one_cmd, " ");
		one_cmd_splited = ft_split(one_cmd_trimed, ' ');
		if (split_by_pipes[i + 1] == NULL)
		{
			printf("뒤에 파이프가 없다. stdout으로 출력하자.\n");
			passing_to_stdout(one_cmd_splited, one_cmd_trimed, setting);
		}
		else
		{
			printf("뒤에 파이프가 더 있다.\n");
			passing_to_pipe(one_cmd_splited, setting);
		}

		free_split(one_cmd_splited);
		free(one_cmd_trimed);
		i++;
	}
	close(setting->pipe_fd[READ]);
	close(setting->pipe_fd[WRITE]);
	return (1);
}

int execute_multi_commands(t_list *cmd, t_setting *setting)
{
	int split_index = 0;
	char **argv = NULL;
	while (cmd != NULL)
	{
		if (-1 == execute_command(cmd->split_by_pipes, setting))
		{
			printf("execute_command error\n");
		}
		free_split(cmd->split_by_pipes);
		cmd = cmd->next;
	}
	return (1);
}