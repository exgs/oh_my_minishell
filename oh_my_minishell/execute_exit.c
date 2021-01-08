/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunslee <yunslee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 21:30:41 by jikang            #+#    #+#             */
/*   Updated: 2021/01/09 03:30:43 by yunslee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* 숫자만 있으면 1, 숫자 아닌 것도 있으면 0 */
static int	is_numeric(char *str)
{
	int	len;

	len = ft_strlen(str);
	if (len == 0)
		return (0);
	else if (len == 1 && !ft_isdigit(str[0]))
		return (0);
	else
	{
		if (*str == '-' || *str == '+')
			str++;
		while (*str)
		{
			if (!ft_isdigit(*str))
				return (0);
			str++;
		}
	}
	return (1);
}

static void one_argv(char *argv)
{
	/* 숫자만 있냐 아니냐? 판단하기 */
	if (is_numeric(argv))
	{
		ft_putendl_fd("exit", 1);
		exit((unsigned char)ft_atoi(argv));
	}
	else
	{
		ft_putendl_fd("exit", 1);
		ft_putstr_fd("bash: exit: ", 1);
		ft_putstr_fd(argv, 1);
		ft_putendl_fd(": numeric argument required", 1);
		exit(255);
	}
}

static void more_than_one_argv(char *argv)
{
	/* 숫자만 있냐 아니냐? 판단하기 */
	if (is_numeric(argv))
	{
		ft_putendl_fd("exit", 1);
		ft_putendl_fd("bash: exit: too many arguments", 1);
		// exit(1); // <== 이 경우에는 종료 안됨 하지만 exitcode가 1이 되는 건 맞음.
		g_status = 1 * 256;
	}
	else
	{
		ft_putendl_fd("exit", 1);
		ft_putstr_fd("bash: exit: ", 1);
		ft_putstr_fd(argv, 1);
		ft_putendl_fd(": numeric argument required", 1);
		exit(255);
	}
}

int execute_exit(const char *path, char *const argv[], char *const envp[])
{
	char **cmd_splited = get_param()->cmd_splited;
	int i;

	i = 0;
	// printf("cmd_splited[0]: %s\n", cmd_splited[0]);
	while (cmd_splited[i] != NULL)
		i++;
	/* i = 1 일 경우, 명령어 제대로 들어옴 */
	if (i == 1)
	{
		// printf("i: %i\n", i);
		exit(g_status);
	}
	/* i = 2 일 경우, 명령어 제대로 들어옴 */
	/* cmd_splited[2] 에 숫자가 아닌 문자가 하나라도 있다면 문자 취급 */
	if (i == 2)
	{
		// printf("i: %i\n", i);
		// printf("cmd_splited[1]: %s\n", cmd_splited[1]);
		one_argv(cmd_splited[1]);
	}
	else
	{
		// printf("i: %i\n", i);
		// printf("cmd_splited[1]: %s\n", cmd_splited[1]);
		// printf("cmd_splited[2]: %s\n", cmd_splited[2]);
		more_than_one_argv(cmd_splited[1]);
	}
	return (1);
}