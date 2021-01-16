#include "minishell.h"

int	msg_error(char *program, char *cmd, char *arg, int exit_status)
{
	ft_putstr_fd(program, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(": ", 2);
	if (exit_status == 2)
		ft_putendl_fd("incorrect usage", 2);
	g_status = exit_status * 256;
	return (-1);
}
