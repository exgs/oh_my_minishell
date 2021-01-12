#include "minishell.h"

int execute_dqmark(const char *path, char *const argv[], char *const envp[])
{
	ft_putstr_fd("bash: ", 1);
	ft_putnbr_fd(g_status / 256, 1);
	ft_putendl_fd(": command not found", 1);
	g_status = 127 * 256;
	return (0);
}