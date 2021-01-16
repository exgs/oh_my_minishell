#include "minishell.h"
#include <stdio.h>

int main(int argc, char *argv[], char **envp)
{
	t_list *cmds = NULL;
	char *line;

	minishell_init(argc, argv, envp); // <-- semi_arr 가 초기화
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
			{
				ft_putendl_fd("exit", 1);
				exit(0);
			}
			g_flag[CTRL_D] = 1;
		}
		ft_memset(g_flag, 0, sizeof(int) * F_END);
		get_commands_from_gnl(&cmds, line);
		execute_multi_commands(cmds);
		free(line);
		ft_lstclear(&cmds, NULL);
	}
	minishell_exit(cmds);
	return (0);
}
