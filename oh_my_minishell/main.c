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


void input_raw_cmd(t_list **cmd, char *line)
{
	char *substr;
	t_list *add;

	while (TRUE)
	{
		substr = ft_strsep(&line, " ");
		if (substr == NULL)
			break ;
		if (ft_strlen(substr) == 0)
			continue ;
		add = ft_lstnew(substr);
		add->i_cmd = which_command(add);
		ft_lstadd_back(cmd, add);
	}
}

void print_cmd(t_list *cmd)
{
	int i;
	int lst_length;

	i = 0;
	lst_length = ft_lstsize(cmd);
	while (i < lst_length)
	{
		printf("%d번 째 cmd: %s i_cmd : %d\n", i, cmd->content, cmd->i_cmd);
		cmd = cmd->next;
		i++;
	}
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


char **input_double_argv(t_list *cmd)
{
	if (cmd->i_cmd == -1)
	{
		printf("Error i_cmd : -1\n");
		return (NULL);
	}
}

char **input_argv(t_list *cmd)
{
	int i = 0;
	while (cmd->i_cmd != -1)
	{
		
		i++;
	}
}

int command_execve(t_list *cmd, char **envp)
{
	int index;
	int pid;
	char **argv;
	char *str[4] = {
		"ls",
		// "-a"
		// "-l",
		0
	};
	printf("%d\n", index = which_command(cmd));
	index = which_command(cmd);
	if (index == -1)
	{
		printf("i_cmd == -1, no fork()\n");
	}
	if (index == LS)
	{
		if (-1 == (pid = fork()))
		{
			printf("fork() error\n");
			return (-1);
		}
		if (pid == 0)
		{
			printf("children fork\n");
			execve("/bin/ls", str, envp);
		}
		else
		{
			printf("parent fork\n");
			wait(NULL);
		}
	}
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
			/* Ctrl + D 누르면 EOF 되어 exit minishell 누르는 함수가 있다고 가정 */
			input_raw_cmd(&cmd, line);
			print_cmd(cmd);
			command_execve(cmd, envp);
			free(line);
		}
		ft_lstclear(&cmd, NULL);
	}
	return (0);
}
