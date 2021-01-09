#include "minishell.h"
#include <stdio.h>

int main(int argc, char *argv[], char **envp)
{
	t_list *cmds = NULL;

	minishell_init(argc, argv, envp);
	catch_signals();
	char *line;
	get_param()->envp = vector_dup(envp);
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
		ft_memset(g_flag, 0, sizeof(int) * F_END);
		get_commands_from_gnl(&cmds, line);
		// print_cmd_list(cmds); // linked list에 들어가있는 값을 '확인차' 출력해봄
		execute_multi_commands(cmds);
		free(line);
		ft_lstclear(&cmds, NULL);
	}
	vector_clear(get_param()->envp);
	return (0);
}
