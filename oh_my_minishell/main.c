/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jikang <jikang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 16:03:39 by jikang            #+#    #+#             */
/*   Updated: 2021/01/22 15:27:43 by jikang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_addchr(char **s, char c)
{
	char	*ret;
	int		count;

	if (*s)
		count = strlen(*s) + 2;
	else
		count = 2;
	ret = ft_calloc(count, sizeof(char));
	if (*s)
		ft_strlcpy(ret, *s, count);
	if (c != '\n')
		ret[count - 2] = c;
	if (*s != NULL)
		free(*s);
	*s = ret;
}

static int	process_g_flag_b(t_list *cmds, char *line)
{
	if (g_flag[CTRL_D] == 1)
	{
		if (line == NULL)
		{
			ft_putendl_fd("exit", 1);
			minishell_exit(cmds);
			exit(0);
		}
		else
			ft_putstr_fd("\n", 1);
	}
	else if (g_flag[CTRL_BS] == 1 && line == NULL)
	{
		g_flag[CTRL_BS] = 0;
		return (1);
	}
	return (0);
}

static int	process_g_flag_a(char **line, char *c)
{
	if (g_flag[CTRL_C])
		g_flag[CTRL_C] = 0;
	else
		ft_putstr_fd("minishell$ ", 1);
	while (1 == (g_flag[CTRL_D] = 1) && read(0, c, 1))
	{
		g_flag[CTRL_D] = 0;
		ft_addchr(line, *c);
		if (*c == '\n')
			break ;
	}
	return (0);
}

int			main(int argc, char *argv[], char **envp)
{
	t_list	*cmds;
	char	*line;
	char	c;

	cmds = NULL;
	line = NULL;
	minishell_init(argc, argv, envp);
	catch_signals();
	g_status = 0;
	while (TRUE)
	{
		process_g_flag_a(&line, &c);
		if (1 == process_g_flag_b(cmds, line))
			continue ;
		ft_memset(g_flag, 0, sizeof(int) * F_END);
		get_commands_from_gnl(&cmds, line);
		execute_multi_commands(cmds);
		free(line);
		line = NULL;
		ft_lstclear(&cmds, NULL);
	}
	minishell_exit(cmds);
	return (0);
}
