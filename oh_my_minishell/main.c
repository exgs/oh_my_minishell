#include "minishell.h"
#include <stdio.h>

int main(int argc, char *argv[], char **envp)
{
	t_list *cmds = NULL;
	char *line;

	minishell_init(argc, argv, envp);
	catch_signals();
	g_status = 0; // $? 의 코드
	while (TRUE)
	{
		if (g_flag[CTRL_BS])
			g_flag[CTRL_BS] = 0;
		else
			ft_putstr_fd("minishell$ ",1);
		while (!(get_next_line(0, &line)))
		{
			if (!g_flag[CTRL_D] && !line[0])
				exit(0);
			g_flag[CTRL_D] = 1;
		}
		get_commands_from_gnl(&cmds, line);
		execute_multi_commands(cmds);
		free(line);
		ft_lstclear(&cmds, NULL);
	}
	minishell_exit(cmds);
	return (0);
}
