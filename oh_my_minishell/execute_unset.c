/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunslee <yunslee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 05:17:20 by ykoh              #+#    #+#             */
/*   Updated: 2021/01/27 19:31:31 by yunslee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	erase_env(char *argv[], char *envp[], int i, int j)
{
	char	*eq;
	int		ret;

	ret = ft_strncmp(envp[j], argv[i], ft_strlen(argv[i]) + 1);
	eq = ft_strchr(envp[j], '=');
	if ((eq && ret == '=') || (!eq && ret == '\0'))
	{
		free(envp[j]);
		while (envp[j])
		{
			envp[j] = envp[j + 1];
			j++;
		}
	}
}

static int	is_valid(char str[])
{
	char	*p;

	p = str;
	if (ft_isdigit(str[0]))
	{
		msg_invalid("minishell", "export", p, 1);
		return (0);
	}
	while (*str)
	{
		if (!ft_isalnum(*str) && !(*str == '_'))
		{
			msg_invalid("minishell", "export", p, 1);
			return (0);
		}
		str++;
	}
	return (1);
}

void		change_argv(char **argv)
{
	int		i;
	char	*tmp;

	i = 0;
	while (argv[i])
	{
		if ((tmp = refine_line(argv[i])))
		{
			free(argv[i]);
			argv[i] = tmp;
		}
		i++;
	}
}

int			execute_unset(const char *path, char *const argv[],
											char *const envp[])
{
	int		i;
	int		j;

	change_argv((char **)++argv);
	i = 0;
	while (argv[i])
	{
		if (is_valid(argv[i]))
		{
			j = 0;
			while (envp[j])
			{
				erase_env((char **)argv, (char **)envp, i, j);
				j++;
			}
		}
		i++;
	}
	if (g_status != 256)
		g_status = 0;
	return (0);
	(void)path;
}
