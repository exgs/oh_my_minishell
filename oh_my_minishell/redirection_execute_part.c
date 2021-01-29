/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_execute_part.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jikang <jikang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 01:27:54 by yunslee           #+#    #+#             */
/*   Updated: 2021/01/27 21:35:30 by jikang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	redirect_left(int i)
{
	int		fd;
	char	*path;

	path = get_param()->cmd_redirect[i + 1][0];
	// if (get_param()->cmd_redirect[i + 1][1] != NULL)
	// 	return (-1);
	fd = open(path, O_RDONLY);
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (1);
}

static int	redirect_right(int i)
{
	int		fd;
	char	*path;

	path = get_param()->cmd_redirect[i + 1][0];
	// if (get_param()->cmd_redirect[i + 1][1] != NULL)
	// 	return (-1);
	fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0755);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (1);
}

static int	redirect_d_right(int i)
{
	int		fd;
	char	*path;

	path = get_param()->cmd_redirect[i + 1][0];
	// if (get_param()->cmd_redirect[i + 1][1] != NULL)
	// 	return (-1);
	fd = open(path, O_WRONLY | O_CREAT | O_APPEND, 0755);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (1);
}

static int	redirect_symbol(char *symbols, int i)
{
	if (symbols[i] == LEFT)
	{
		if (-1 == redirect_left(i))
			return (-1);
	}
	else if (symbols[i] == RIGHT)
	{
		if (-1 == redirect_right(i))
			return (-1);
	}
	else if (symbols[i] == D_RIGHT)
	{
		if (-1 == redirect_d_right(i))
			return (-1);
	}
	return (1);
}

int			execute_nopipe_redirect(void)
{
	char	*symbols;
	int		i;

	i = 0;
	symbols = get_param()->symbol_array;
	while (symbols[i] != 0)
	{
		if (-1 == (redirect_symbol(symbols, i)))
			return (-1);
		i++;
	}
	check_command(get_param()->cmd_redirect[0][0],
					get_param()->cmd_redirect[0], get_param()->envp);
	dup_initalize();
	return (1);
}
