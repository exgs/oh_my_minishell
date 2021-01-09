#include "minishell.h"


void	minishell_init(int argc, char **argv, char **envp)
{
	ft_memset(g_flag, 0, sizeof(int) * F_END);
	g_dup_stdin = dup(STDIN_FILENO);
	g_dup_stdout = dup(STDOUT_FILENO);
	get_param()->cmd_trimed = NULL;
	get_param()->cmd_splited = NULL;
	get_param()->cmd_redirect = NULL;
	get_param()->symbol_array = NULL;
	get_param()->envp = vector_dup(envp);
	catch_signals();
}

void	minishell_exit(t_list *cmds)
{
	t_data *data;
	data = get_param();
	if (data->cmd_trimed != NULL)
		free(data->cmd_trimed);
	data->cmd_trimed = NULL;
	if (data->cmd_splited != NULL)
		free_split(data->cmd_splited);
	data->cmd_splited = NULL;
	if (data->cmd_redirect != NULL)
		free_3d_split(data->cmd_redirect);
	data->cmd_redirect = NULL;
	if (data->symbol_array != NULL)
		free(data->symbol_array);
	data->symbol_array = NULL;
	if (cmds->split_by_pipes != NULL)
		free_split(cmds->split_by_pipes);
	cmds->split_by_pipes = NULL;
	vector_clear(data->envp);
	close(g_dup_stdout);
	close(g_dup_stdin);
}

void	cmds_exit(t_list *cmds)
{
	t_data *data;
	data = get_param();
	if (data->cmd_trimed != NULL)
		free(data->cmd_trimed);
	data->cmd_trimed = NULL;
	if (data->cmd_splited != NULL)
		free_split(data->cmd_splited);
	data->cmd_splited = NULL;
	if (data->cmd_redirect != NULL)
		free_3d_split(data->cmd_redirect);
	data->cmd_redirect = NULL;
	if (data->symbol_array != NULL)
		free(data->symbol_array);
	data->symbol_array = NULL;
	if (cmds->split_by_pipes != NULL)
		free_split(cmds->split_by_pipes);
	cmds->split_by_pipes = NULL;
}

void	cmd_exit()
{
	t_data *data;
	data = get_param();
	if (data->cmd_trimed != NULL)
		free(data->cmd_trimed);
	data->cmd_trimed = NULL;
	if (data->cmd_splited != NULL)
		free_split(data->cmd_splited);
	data->cmd_splited = NULL;
	if (data->cmd_redirect != NULL)
		free_3d_split(data->cmd_redirect);
	data->cmd_redirect = NULL;
	if (data->symbol_array != NULL)
		free(data->symbol_array);
	data->symbol_array = NULL;
}

void	dup_initalize()
{
	dup2(g_dup_stdin, STDIN_FILENO);
	dup2(g_dup_stdout, STDOUT_FILENO);
}