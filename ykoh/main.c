#include "minishell.h"

t_data		*get_param()
{
	static t_data	param;

	return (&param);
}

int main(int argc, char *argv[], char *envp[])
{
	get_param()->envp = vector_dup(envp);
	get_param()->argv = vector_dup(argv);


	ft_export("export", get_param()->argv, get_param()->envp);

//	ft_unset("unset", get_param()->argv, get_param()->envp);

 	ft_env("env", get_param()->argv, get_param()->envp);

	return (0);
	(void)argc;
	(void)argv;
	(void)envp;
}