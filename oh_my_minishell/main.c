#include "minishell.h"
#include <stdio.h>

int main(int argc, char *argv[], char **envp)
{
	t_list *cmds = NULL;
	t_setting setting;
	setting.envp = envp;
	char *line;
	get_param()->exit_status = 0; // exit 할 때, error 코드 초기화

	while (TRUE)
	{
		ft_putstr_fd("bash-3.2$ ", 1);
		if (get_next_line(0, &line) >  0)
		{
			get_commands_from_gnl(&cmds, line, &setting);
			// print_cmd_list(cmds); // linked list에 들어가있는 값을 '확인차' 출력해봄
			execute_multi_commands(cmds, &setting);
			free(line);
		}
		ft_lstclear(&cmds, NULL);
	}
	return (0);
}
