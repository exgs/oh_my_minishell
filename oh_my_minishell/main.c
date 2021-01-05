#include "minishell.h"
#include <stdio.h>

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
	else
		return (-1);
}



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

int command_execve(int i_cmd, char **argv, char **envp)
{
	int pid;
	if (i_cmd == -1)
	{
		printf("i_cmd == -1, no fork()\n");
		return (1);
	}
	if (i_cmd == LS)
	{
		if (-1 == (pid = fork()))
		{
			printf("fork() error\n");
			return (-1);
		}
		if (pid == 0)
		{
			printf("children fork\n");
			execve("/bin/ls", argv, envp);
		}
		else
		{
			printf("parent fork\n");
			wait(NULL);
		}
	}
	if (i_cmd == ECHO)
	{
		if (-1 == (pid = fork()))
		{
			printf("fork() error\n");
			return (-1);
		}
		if (pid == 0)
		{
			printf("children fork\n");
			execve("/bin/echo", argv, envp);
		}
		else
		{
			printf("parent fork\n");
			wait(NULL);
		}
	}
	if (i_cmd == CD) //built-in 함수를 써야함
	{
		printf("CD command\n");
		int buf[100];
		chdir(argv[1]);
		// getcwd(buf,100);
	}
	if (i_cmd == PWD)
	{
		if (-1 == (pid = fork()))
		{
			printf("fork() error\n");
			return (-1);
		}
		if (pid == 0)
		{
			printf("children fork\n");
			execve("/bin/pwd", argv, envp);
		}
		else
		{
			printf("parent fork\n");
			wait(NULL);
		}
	}
	if (i_cmd == EXPORT)
	{
		if (-1 == (pid = fork()))
		{
			printf("fork() error\n");
			return (-1);
		}
		if (pid == 0)
		{
			printf("children fork\n");
			execve("/bin/sh", argv, envp);
		}
		else
		{
			printf("parent fork\n");
			wait(NULL);
		}
	}
	if (i_cmd == UNSET)
	{
/*
		if (-1 == (pid = fork()))
		{
			printf("fork() error\n");
			return (-1);
		}
*/
		if (pid == 0)
		{
//			printf("children fork\n");
//			execve("/bin/sh", argv, envp);
			ft_unset("안쓰임", argv, envp);
		}
		else
		{
			printf("parent fork\n");
			wait(NULL);
		}
	}
	if (i_cmd == ENV)
	{
/*
		if (-1 == (pid = fork()))
		{
			printf("fork() error\n");
			return (-1);
		}
*/
		if (pid == 0)
		{
//			printf("children fork\n");
//			execve("/usr/bin/env", argv, envp);
			ft_env("안쓰임", argv, envp);
		}
		else
		{
			printf("parent fork\n");
			wait(NULL);
		}
	}
	if (i_cmd == EXIT) //built-in 함수 써야함
		exit(0);
	return (1);
}

int commands_execve(t_list *cmd, char **envp)
{
	int index;
	int pid;
	char **argv = NULL;
	t_list *head = cmd;
	while (cmd != NULL)
	{
		argv = cmd->split;
		// print_double_argv(argv);
		command_execve(cmd->i_cmd, argv, envp); //정상적으로 들어왔을 때의 한해서
		free_split(argv);
		cmd = cmd->next;
	}
	return 1;
}

t_data		*get_param()
{
	static t_data	param;

	return (&param);
}

int main(int argc, char *argv[], char **envp)
{
	t_list *cmds = NULL;
	char *line;

	get_param()->envp = vector_dup(envp); // 구조체에 복사하게

	while (TRUE)
	{
		ft_putstr_fd("bash-3.2$ ", 1);
		if (get_next_line(0, &line) >  0)
		{
			get_cmd_from_gnl(&cmds, line); //먼저 ';'을 기준으로 string이 각각의 노드에 나눠들어가도록하고 그안에서 split해줌
			// | 로도 나눠줘야하는데 아직 못함
			
			// print_cmd_list(cmds); // linked list에 들어가있는 값을 '확인차' 출력해봄
			commands_execve(cmds, get_param()->envp);
			free(line);
		}
		ft_lstclear(&cmds, NULL);
	}
	vector_clear(get_param()->envp);
	free(get_param());
	return (0);
}
