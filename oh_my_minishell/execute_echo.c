/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunslee <yunslee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 23:06:26 by jikang            #+#    #+#             */
/*   Updated: 2021/01/26 02:41:34 by yunslee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			skip_n_option(char *str, int *i, int *flag_n)
{
	int			j;

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

/*
** name : execute_echo
** aim : echo, /bin/echo command process
** only -n option works (-n: skip new line)
*/

int				execute_echo(const char *path, char *const argv[],
								char *const envp[])
{
	int			i;
	int			flag_n;
	char		*echo_line;

	i = 5;
	flag_n = 0;
	if (ft_strncmp(get_param()->cmd_trimed, "/bin/echo", 9) == 0)
		i = 10;
	echo_line = refine_line(get_param()->cmd_trimed);
	if (echo_line == NULL)
		return (0);
	skip_n_option(echo_line, &i, &flag_n);
	while (echo_line[i] != '\0')
		ft_putchar_fd(echo_line[i++], 1);
	if (flag_n != 1)
		ft_putchar_fd('\n', 1);
	free(echo_line);
	g_status = 0;
	return (0);
	(void)path;
	(void)argv;
	(void)envp;
}
