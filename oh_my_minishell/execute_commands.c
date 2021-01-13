#include "minishell.h"

static void error_except()
{
	if (g_except[SYNTAX] != 0)
	{
		ft_putstr_fd("minishell: parse error near '", 1);
		ft_putchar_fd(g_except[SYNTAX], 1);
		ft_putstr_fd("'\n", 1);
	}
	g_except[SYNTAX] = 0;
}

int execute_command(char **split_by_pipes)
{
	int fd[2];
	int i = 0;

	if (split_by_pipes[0] == NULL)
	{
		g_except[SYNTAX] = '|';
		return (-1);
	}
	if (split_by_pipes[1] == NULL)
	{
		if (-1 == (execute_command_nopipe(split_by_pipes[0])))
		{
			ft_putstr_fd("Error:execute_command_nopipe\n", 1);
			return (-1);
		}
		return (1);
	}
	pipe(fd);
	execute_command_pipe(split_by_pipes, fd, 0);
	dup2(g_dup_stdin, STDIN_FILENO);
	cmd_exit();
	return (1);
}

int execute_multi_commands(t_list *cmds)
{
	int split_index = 0;
	char **argv = NULL;
	t_list *cur = cmds;
	while (cur != NULL)
	{
		if (-1 == execute_command(cur->split_by_pipes))
		{
			printf("execute_command error\n");
			error_except();
		}
		cmd_exit();
		cur = cur->next;
	}
	cmds_exit(cmds);
	return (1);
}