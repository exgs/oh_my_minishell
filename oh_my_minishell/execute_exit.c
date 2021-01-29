/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jikang <jikang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 21:30:41 by jikang            #+#    #+#             */
/*   Updated: 2021/01/29 16:43:20 by jikang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** name : is_numeric
** aim : distinguish nums(also with pos, neg sign)
*/

static int				is_numeric(char *str)
{
	int					len;

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

/*
** name : one_argv
** @if : argv contains only nums
** @else : argv contains not number
*/

static void				one_argv(char *argv)
{
	if (is_numeric(argv))
	{
		ft_putendl_fd("exit", 2);
		exit((unsigned char)ft_atoi(argv));
	}
	else
	{
		ft_putendl_fd("exit", 2);
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(argv, 2);
		ft_putendl_fd(": numeric argument required", 2);
		exit(255);
	}
}

/*
** name : more_than_one_argv
** @if : argv contains only nums
** @else : argv contains not number
*/

static void				more_than_one_argv(char *argv)
{
	if (is_numeric(argv))
	{
		ft_putendl_fd("exit", 2);
		ft_putendl_fd("minishell: exit: too many arguments", 2);
		g_status = 1 * 256;
	}
	else
	{
		ft_putendl_fd("exit", 2);
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(argv, 2);
		ft_putendl_fd(": numeric argument required", 2);
		exit(255);
	}
}

/*
** name : change_split
** aim : convert change argv[1]
*/

static void				change_split(char **argv)
{
	char *str;

	str = refine_line(argv[1]);
	free_swap(&argv[1], str);
}

/*
** name : execute_exit
** aim : program exits with correct exit code
** i == 1 : basic exit
** i == 2 : exit with certain code
** else : too many certain codes
*/

int						execute_exit(const char *path,
				char *const argv[], char *const envp[])
{
	char		**cmd_splited;
	int			i;

	cmd_splited = get_param()->cmd_splited;
	i = 0;
	change_split(cmd_splited);
	while (cmd_splited[i] != NULL)
		i++;
	if (i == 1)
	{
		ft_putendl_fd("exit", 2);
		exit(g_status * 256);
	}
	if (i == 2)
		one_argv(cmd_splited[1]);
	else
		more_than_one_argv(cmd_splited[1]);
	return (1);
	(void)path;
	(void)argv;
	(void)envp;
}
