#include "minishell.h"
#include <stdio.h>

static void ft_addchr(char **s, char c)
{
	char	*ret;
	int		count;

	if (*s)
		count = strlen(*s) + 2;
	else
		count = 2;
	ret = calloc(count, sizeof(char));
	if (*s)
		strlcpy(ret, *s, count);
	ret[count - 2] = c;
	free(*s);
	*s = ret;
}

int main(int argc, char *argv[], char **envp)
{
	t_list *cmds = NULL;
	char *line;
	char c;

	minishell_init(argc, argv, envp); // <-- semi_arr 가 초기화
	catch_signals();
	g_status = 0; // $? 의 코드
	while (TRUE)
	{
		if (g_flag[CTRL_BS])
			g_flag[CTRL_BS] = 0;
		else
			ft_putstr_fd("minishell$ ",1);
		while (read(0, &c, 1) && c != '\n')
		{
			ft_addchr(&line, c);
		}
		if (c == '\0')
		{
			ft_putendl_fd("exit", 1);
			minishell_exit(cmds); exit(0);
		}
		ft_memset(g_flag, 0, sizeof(int) * F_END);
		get_commands_from_gnl(&cmds, line);
		execute_multi_commands(cmds);
		free(line);
		line = NULL;
		ft_lstclear(&cmds, NULL);
	}
	minishell_exit(cmds);
	return (0);
}
