#include "minishell.h"

void	catch_sigint(int pid)
{
	(void)pid;
	ft_putstr_fd("\nminishell$ ", 1);
	g_flag[CTRL_BS] = 1;
}

void	catch_sigquit(int pid)
{
	pid = waitpid(-1, &g_status, WNOHANG);
	if (!pid)
		ft_putstr_fd("Quit: 3\n", 1);
}

void	catch_signals(void)
{
	signal(SIGINT, catch_sigint);
	signal(SIGQUIT, catch_sigquit);
}
