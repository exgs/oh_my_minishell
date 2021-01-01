#include "minishell.h"

char **get_double_argv(t_list *cmd)
{
	char **argv;
	t_list *temp;
	temp = cmd->next;
	int size = 1;
	int j = 0;
	while (temp != NULL && temp->i_cmd == -1)
	{
		temp = temp->next;
		size++;
	}
	// size = 10;
	argv = malloc(sizeof(char *) * (size + 1));
	printf("size : %d\n", size);
	while (j < size)
	{
		if (cmd == NULL)
			break;
		argv[j] = ft_strdup(cmd->content);
		cmd = cmd->next;
		j++;
	}
	argv[j] = NULL;
	return (argv);
}

void print_double_argv(char **argv)
{
	if (argv == NULL)
		return ;
	int i = 0;
	while (argv[i])
	{
		printf("%d번째:%s\n", i, argv[i]);
		i++;
	}
}

void free_double_argv(char **argv)
{
	int i = 0;
	char *temp;
	if (argv == NULL)
		return ;
	while (argv[i] != NULL)
	{
		temp = argv[i];
		free(temp);
		i++;
	}
	free(argv);
}