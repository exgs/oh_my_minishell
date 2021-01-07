#include "minishell.h"


void	minishell_init(int argc, char **argv, char **envp)
{
	ft_memset(g_flag, 0, sizeof(int) * F_END);
	catch_signals();
}