/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msg_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykoh <ykoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 05:17:30 by ykoh              #+#    #+#             */
/*   Updated: 2021/01/21 05:17:31 by ykoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	msg_error(char *program, char *cmd, char *arg, int exit_status)
{
	ft_putstr_fd(program, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(": ", 2);
	if (exit_status == 2)
		ft_putendl_fd("incorrect usage", 2);
	g_status = exit_status * 256;
	return (-1);
}

int	msg_invalid(char *program, char *cmd, char *arg, int exit_status)
{
	ft_putstr_fd(program, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": `", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd("': ", 2);
	ft_putendl_fd(": not a valid identifier", 2);
	g_status = exit_status * 256;
	return (-1);
}

int	msg_syntax(char *program, char arg, int exit_status)
{
	ft_putstr_fd(program, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd("syntax error near unexpected token `", 2);
	if (arg == '>' || arg == '<')
		ft_putstr_fd("newline", 2);
	else
		ft_putchar_fd(arg, 2);
	ft_putendl_fd("'", 2);
	g_status = exit_status * 256;
	return (-1);
}
