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

int execve_nopipe(int num_cmd, char **argv, t_setting *setting)
{
	int pid;
	int *pipe_fd;
	int temp;
	
	pipe_fd = setting->pipe_fd;
	if (num_cmd == LS)
	{
		if (-1 == (pid = fork()))
		{
			// printf("fork() error\n");
			return (-1);
		}
		if (pid == 0)
		{
			// printf("children fork\n");
			execve("/bin/ls", argv, setting->envp);
		}
		else
		{
			// printf("parent fork\n");
			wait(NULL);
		}
	}
	if (num_cmd == ECHO)
	{
		if (-1 == (pid = fork()))
		{
			// printf("fork() error\n");
			return (-1);
		}
		if (pid == 0)
		{
			// printf("children fork\n");
			execve("/bin/echo", argv, setting->envp);
		}
		else
		{
			// printf("parent fork\n");
			wait(NULL);
		}
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
		if (-1 == (pid = fork()))
		{
			// printf("fork() error\n");
			return (-1);
		}
		if (pid == 0)
		{
			// printf("children fork\n");
			execve("/bin/pwd", argv, setting->envp);
		}
		else
		{
			// printf("parent fork\n");
			wait(NULL);
		}
	}
	if (num_cmd == EXPORT)
	{
		if (-1 == (pid = fork()))
		{
			// printf("fork() error\n");
			return (-1);
		}
		if (pid == 0)
		{
			// printf("children fork\n");
			execve("/bin/sh", argv, setting->envp);
		}
		else
		{
			// printf("parent fork\n");
			wait(NULL);
		}
	}
	if (num_cmd == UNSET)
	{
		if (-1 == (pid = fork()))
		{
			// printf("fork() error\n");
			return (-1);
		}
		if (pid == 0)
		{
			// printf("children fork\n");
			execve("/bin/sh", argv, setting->envp);
		}
		else
		{
			// printf("parent fork\n");
			wait(NULL);
		}
	}
	if (num_cmd == ENV)
	{
		if (-1 == (pid = fork()))
		{
			// printf("fork() error\n");
			return (-1);
		}
		if (pid == 0)
		{
			// printf("children fork\n");
			execve("/usr/bin/env", argv, setting->envp);
		}
		else
		{
			// printf("parent fork\n");
			wait(NULL);
		}
	}
	if (num_cmd == EXIT) //built-in 함수 써야함
		exit(0);
	if (num_cmd == GREP)
	{
		temp = dup(STDIN_FILENO);
		if (-1 == (pid = fork()))
		{
			// printf("fork() error\n");
			return (-1);
		}
		if (pid == 0)
		{
			// printf("children fork\n");
			dup2(pipe_fd[READ], STDIN_FILENO);
			execve("/usr/bin/grep", argv, setting->envp);
		}
		else
		{
			// printf("parent fork\n");
			wait(NULL);
			// dup2(temp, STDIN_FILENO);
		}
	}
	return (1);
}

int execve_pipe(int num_cmd, char **argv, t_setting *setting)
{
	int pid;
	int *pipe_fd;
	int temp;
	
	pipe_fd = setting->pipe_fd;
	if (num_cmd == LS)
	{
		temp = dup(STDOUT_FILENO);
		if (-1 == (pid = fork()))
		{
			// printf("fork() error\n");
			return (-1);
		}
		if (pid == 0)
		{
			// close(pipe_fd[READ]);
			// dup2(pipe_fd[READ], STDIN_FILENO);
			dup2(pipe_fd[WRITE], STDOUT_FILENO);
			// printf("children fork\n");
			execve("/bin/ls", argv, setting->envp);
		}
		else
		{
			// close(pipe_fd[WRITE]);
			// printf("parent fork\n");
			wait(NULL);
			dup2(temp, STDOUT_FILENO);
		}
	}
	if (num_cmd == ECHO)
	{
		if (-1 == (pid = fork()))
		{
			// printf("fork() error\n");
			return (-1);
		}
		if (pid == 0)
		{
			// printf("children fork\n");
			execve("/bin/echo", argv, setting->envp);
		}
		else
		{
			// printf("parent fork\n");
			wait(NULL);
		}
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
		if (-1 == (pid = fork()))
		{
			// printf("fork() error\n");
			return (-1);
		}
		if (pid == 0)
		{
			// printf("children fork\n");
			execve("/bin/pwd", argv, setting->envp);
		}
		else
		{
			// printf("parent fork\n");
			wait(NULL);
		}
	}
	if (num_cmd == EXPORT)
	{
		if (-1 == (pid = fork()))
		{
			// printf("fork() error\n");
			return (-1);
		}
		if (pid == 0)
		{
			// printf("children fork\n");
			execve("/bin/sh", argv, setting->envp);
		}
		else
		{
			// printf("parent fork\n");
			wait(NULL);
		}
	}
	if (num_cmd == UNSET)
	{
		if (-1 == (pid = fork()))
		{
			// printf("fork() error\n");
			return (-1);
		}
		if (pid == 0)
		{
			// printf("children fork\n");
			execve("/bin/sh", argv, setting->envp);
		}
		else
		{
			// printf("parent fork\n");
			wait(NULL);
		}
	}
	if (num_cmd == ENV)
	{
		if (-1 == (pid = fork()))
		{
			// printf("fork() error\n");
			return (-1);
		}
		if (pid == 0)
		{
			// printf("children fork\n");
			execve("/usr/bin/env", argv, setting->envp);
		}
		else
		{
			// printf("parent fork\n");
			wait(NULL);
		}
	}
	if (num_cmd == EXIT) //built-in 함수 써야함
		exit(0);
	if (num_cmd == GREP)
	{
		// temp = dup(STDIN_FILENO);
		if (-1 == (pid = fork()))
		{
			// printf("fork() error\n");
			return (-1);
		}
		if (pid == 0)
		{
			// dup2(pipe_fd[READ], STDIN_FILENO);
			// printf("children fork\n");
			execve("/usr/bin/grep", argv, setting->envp);
		}
		else
		{
			// printf("parent fork\n");
			wait(NULL);
			// dup2(temp, STDOUT_FILENO);
		}
	}
	return (1);
}

int passing_to_stdout(char **one_cmd_splited, t_setting *setting)
{
	int num_cmd;
	
	if (-1 == (num_cmd = which_command(one_cmd_splited[0])))
	{
		printf("command not found: %s\n", one_cmd_splited[0]);
		return (-1);
	}
	if (-1 == (execve_nopipe(num_cmd, one_cmd_splited, setting)))
	{
		printf("fork error\n");
		return (-1);
	}
	return (1);
}

int passing_to_pipe(char **one_cmd_splited, t_setting *setting)
{
	int num_cmd;
	
	if (-1 == (num_cmd = which_command(one_cmd_splited[0])))
	{
		printf("command not found: %s\n", one_cmd_splited[0]);
		return (-1);
	}
	if (-1 == (execve_pipe(num_cmd, one_cmd_splited, setting)))
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
			passing_to_stdout(one_cmd_splited, setting);
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