/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jikang <jikang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 21:30:41 by jikang            #+#    #+#             */
/*   Updated: 2021/01/06 23:43:51 by jikang           ###   ########.fr       */
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
		get_param()->exit_status = 1;
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

void execute_exit(char **argv)
{
	int i;

	i = 0;
	// printf("argv[0]: %s\n", argv[0]);
	while (argv[i] != NULL)
		i++;
	/* i = 1 일 경우, 명령어 제대로 들어옴 */
	if (i == 1)
	{
		// printf("i: %i\n", i);
		exit(get_param()->exit_status);
	}
	/* i = 2 일 경우, 명령어 제대로 들어옴 */
	/* argv[2] 에 숫자가 아닌 문자가 하나라도 있다면 문자 취급 */
	if (i == 2)
	{
		// printf("i: %i\n", i);
		// printf("argv[1]: %s\n", argv[1]);
		one_argv(argv[1]);
	}
	else
	{
		// printf("i: %i\n", i);
		// printf("argv[1]: %s\n", argv[1]);
		// printf("argv[2]: %s\n", argv[2]);
		more_than_one_argv(argv[1]);
	}
}