#include "minishell.h"

void skip_n_option(char *str, int *i, int *flag_n)
{
	int j;

	j = *i;
	while (str[j] && str[j + 1] && str[j + 2])
	{
		if (str[j] == '-' && str[j + 1] == 'n' && str[j + 2] == ' ')
		{
			j = j + 3;
			*flag_n = 1;
			*i = j;
		}
		else
			break ;
	}
}

int execute_echo(const char *path, char *const argv[], char *const envp[])
{
	int i;
	int flag_n;
	char *one_cmd_trimed;

	one_cmd_trimed = get_param()->cmd_trimed;
	i = 4;
	flag_n = 0;
	if (ft_strncmp(one_cmd_trimed, "/bin/echo", 9) == 0)
		i = 9;
	while (one_cmd_trimed[i] == ' ')
		i++;
	skip_n_option(one_cmd_trimed, &i, &flag_n);
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