#include "minishell.h"

int is_execve(char *path, char **cmd_splited, char *envp[])
{
	int num_cmd;
	pid_t pid;
	char *temp1 = cmd_splited[1];
	char *temp2 = cmd_splited[2];
	num_cmd = which_command(cmd_splited[0]);
	if (num_cmd == LS)
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
	if (num_cmd == GREP) // Grep을 단독으로 썼을 떄에 대해서는 따로 구별해야할 듯
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
	if (num_cmd == CLEAR)
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
	if (num_cmd == CAT)
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
}