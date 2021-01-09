#include "minishell.h"

int execute_command(char **split_by_pipes)
{
	int fd[2];
	int i = 0;

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
		}
		cmd_exit();
		cur = cur->next;
	}
	cmds_exit(cmds);
	return (1);
}