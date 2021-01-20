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
	if (str[j] == '-' && str[j + 1] == 'n' && str[j + 2] == '\0')
	{
		j = j + 2;
		*flag_n = 1;
		*i = j;
	}
}

int execute_echo(const char *path, char *const argv[], char *const envp[])
{
	int i;
	int flag_n;
	char *one_cmd_trimed;
	char *echo_line;

	one_cmd_trimed = get_param()->cmd_trimed;
	// ft_putendl_fd(one_cmd_trimed, 1);
	i = 4;
	flag_n = 0;
	if (ft_strncmp(one_cmd_trimed, "/bin/echo", 9) == 0)
		i = 9;
	/* 여기서 quotes 있으면 멈춰줘야함. */
	while (one_cmd_trimed[i] == ' ')
		i++;
	skip_n_option(one_cmd_trimed, &i, &flag_n);
	/* 여기서 큰 따옴표, 작은 따옴표 처리 */
	echo_line = refine_line(one_cmd_trimed);
	if (echo_line == NULL)
		return (0);
	while (echo_line[i] != '\0')
	{
		ft_putchar_fd(echo_line[i], 1);
		i++;
	}
	/* -n 옵션 들어갈 시 무시 */
	if (flag_n != 1)
		ft_putchar_fd('\n', 1);
	if (echo_line == NULL)
		return (0);
	free(echo_line);
	g_status = 0;
	return (0);
}