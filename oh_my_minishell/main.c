#include "minishell.h"
#include <stdio.h>

int which_command(t_list *cmd)
{
	if (!ft_strncmp(string_tolower(cmd->content),"echo",10))
		return (ECHO);
	if (!ft_strncmp(string_tolower(cmd->content),"cd",10))
		return (CD);
	if (!ft_strncmp(string_tolower(cmd->content),"pwd",10))
		return (PWD);
	if (!ft_strncmp(string_tolower(cmd->content),"export",10))
		return (EXPORT);
	if (!ft_strncmp(string_tolower(cmd->content),"unset",10))
		return (UNSET);
	if (!ft_strncmp(string_tolower(cmd->content),"env",10))
		return (ENV);
	if (!ft_strncmp(string_tolower(cmd->content),"exit",10))
		return (EXIT);
	if (!ft_strncmp(string_tolower(cmd->content),"ls",10))
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
			execve("/bin/export", argv, envp);
		}
		else
		{
			printf("parent fork\n");
			wait(NULL);
		}
	}
	if (i_cmd == UNSET)
	{
		if (-1 == (pid = fork()))
		{
			printf("fork() error\n");
			return (-1);
		}
		if (pid == 0)
		{
			printf("children fork\n");
			execve("/bin/unset", argv, envp);
		}
		else
		{
			printf("parent fork\n");
			wait(NULL);
		}
	}
	if (i_cmd == ENV)
	{
		if (-1 == (pid = fork()))
		{
			printf("fork() error\n");
			return (-1);
		}
		if (pid == 0)
		{
			printf("children fork\n");
			execve("/bin/env", argv, envp);
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
	argv = get_double_argv(cmd);
	// print_double_argv(argv);
	command_execve(cmd->i_cmd, argv, envp); //정상적으로 들어왔을 때의 한해서
	free_double_argv(argv);
	return 1;
}


int main(int argc, char *argv[], char **envp)
{
	t_list *cmd;
	char *line;
	cmd = NULL;
	while (TRUE)
	{
		ft_putstr_fd("bash-3.2$ ", 1);
		if (get_next_line(0, &line) >  0)
		{
			input_raw_cmd(&cmd, line); // 오직 띄어쓰기만을 기준으로 나누어서 void *content에 넣어준다. + i_cmd값
			//영환이 형이 여기서 파싱을 해준다.
			print_cmd_list(cmd); // linked list에 들어가있는 값을 '확인차' 출력해봄
			commands_execve(cmd, envp);
			free(line);
		}
		ft_lstclear(&cmd, NULL);
	}
	return (0);
}
