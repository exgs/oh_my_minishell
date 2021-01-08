#include "minishell.h"


void	minishell_init(int argc, char **argv, char **envp)
{
	ft_memset(g_flag, 0, sizeof(int) * F_END);
	get_param()->cmd_trimed = NULL;
	get_param()->cmd_splited = NULL;
	get_param()->envp = vector_dup(envp);
	catch_signals();
}

void	minishell_exit(t_list *cmds)
{
	if (get_param()->cmd_trimed != NULL)
		free(get_param()->cmd_trimed);
	get_param()->cmd_trimed = NULL;
	if (get_param()->cmd_splited != NULL)
		free_split(get_param()->cmd_splited);
	get_param()->cmd_splited = NULL;
	if (cmds->split_by_pipes != NULL)
		free_split(cmds->split_by_pipes);
	cmds->split_by_pipes = NULL;
	vector_clear(get_param()->envp);
}

void	cmds_exit(t_list *cmds)
{
	if (get_param()->cmd_trimed != NULL)
		free(get_param()->cmd_trimed);
	get_param()->cmd_trimed = NULL;
	if (get_param()->cmd_splited != NULL)
		free_split(get_param()->cmd_splited);
	get_param()->cmd_splited = NULL;
	if (cmds->split_by_pipes != NULL)
		free_split(cmds->split_by_pipes);
	cmds->split_by_pipes = NULL;
}

void	cmd_exit()
{
	if (get_param()->cmd_trimed != NULL)
		free(get_param()->cmd_trimed);
	get_param()->cmd_trimed = NULL;
	if (get_param()->cmd_splited != NULL)
		free_split(get_param()->cmd_splited);
	get_param()->cmd_splited = NULL;
}