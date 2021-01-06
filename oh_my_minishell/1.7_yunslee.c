#include "minishell.h"

int execve_nopipe(int num_cmd, char **argv, char *one_cmd_trimed, t_setting *setting)
{
	int pid;
	int i;

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
	if (num_cmd == GREP) // Grep을 단독으로 썼을 떄에 대해서는 따로 구별해야할 듯
	{
		if (-1 == (pid = fork()))
			return (-1);
		if (pid == 0)
		{
			execve("/usr/bin/grep", argv, setting->envp);
		}
		else
		{
			wait(NULL);
		}
	}
	return (1);
}


int	execute_command_nopipe(char *one_cmd, t_setting *setting)
{
	char *one_cmd_trimed;
	char **one_cmd_splited;
	int num_cmd;
	int temp;

	one_cmd_trimed = ft_strtrim(one_cmd, " ");
	one_cmd_splited = ft_split(one_cmd_trimed, ' ');
	
	if (-1 == (num_cmd = which_command(one_cmd_splited[0])))
	{
		printf("command not found: %s\n", one_cmd_splited[0]);
		return (-1);
	}
	temp = execve_nopipe(num_cmd, one_cmd_splited, one_cmd_trimed, setting);
	if (temp == -1)
	{
		printf("fork error\n");
		return (-1);
	}
	return (1);
}