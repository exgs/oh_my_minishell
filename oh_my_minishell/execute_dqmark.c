#include "minishell.h"

int execute_dqmark(const char *path, char *const argv[], char *const envp[])
{
	int i;	int j;
	char **envlist;
	char buff[BUFF_MAX];
	char *str;

	str = get_param()->cmd_trimed;
	envlist = get_param()->envp;
	/* question mark 가 있으면? */
	i = 0;
	if (path[1] == '?')
	{
		ft_putendl_fd(str, 2);
		ft_putstr_fd("bash: ", 2);
		ft_putnbr_fd(g_status / 256, 2);
		ft_putendl_fd(": command not found", 2);
		g_status = 127 * 256;
		return (0);
	}
	else
	{
		init_array(buff);
		i = 1;
		while (str[i] != '\0')
		{
			buff[i - 1] = str[i];
			i++;
		}
		i = 0;
		while (envlist[i] != NULL)
		{
			/* 우리가 찾는 환경 변수와 일치하다면 buff 에 알맞은 그 값을 넣어 준다. */
			if (ft_strncmp(envlist[i], buff, ft_strlen(buff) + 1) == '=')
			{
				j = ft_strlen(buff) + 1;
				while (envlist[i][j] != '\0')
				{
					ft_putchar_fd(envlist[i][j], 1);
					j++;
				}
				break ;
			}
			i++;
		}
		ft_putchar_fd('\n', 1);
	}
	return (0);
}