#include "minishell.h"

void free_split(char **argv)
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

void print_split(char **split)
{
	if (split == NULL)
		return ;
	int i = 0;
	while (split[i])
	{
		printf("split|%d번째:%s\n", i, split[i]);
		i++;
	}
}

void print_cmd_list(t_list *cmd)
{
	int i;
	int lst_length;

	i = 0;
	lst_length = ft_lstsize(cmd);
	while (i < lst_length)
	{
		printf("linked|%d번째:%s|i_cmd:%d\n", i, cmd->content, cmd->i_cmd);
		cmd = cmd->next;
		i++;
	}
}
