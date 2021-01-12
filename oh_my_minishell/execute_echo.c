#include "minishell.h"

int execute_echo(const char *path, char *const argv[], char *const envp[])
{
	int i;
	int flag_n;
	char *one_cmd_trimed;

	one_cmd_trimed = get_param()->cmd_trimed;
	flag_n = 0;
	i = 4;
	while (one_cmd_trimed[i] == ' ')
		i++;
	if (one_cmd_trimed[i] == '-')
	{
		if (one_cmd_trimed[i + 1] == 'n')
		{
			i = i + 2;
			flag_n = 1;
			while (one_cmd_trimed[i] == ' ')
				i++;
		}
	}
	while (one_cmd_trimed[i] != '\0')
	{
		ft_putchar_fd(one_cmd_trimed[i], 1);
		i++;
	}
	/* -n 옵션 들어갈 시 무시 */
	if (flag_n != 1)
		ft_putchar_fd('\n', 1);
	g_status = 0;
	return (0);
}