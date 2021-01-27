/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_export_a.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunslee <yunslee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 05:17:00 by ykoh              #+#    #+#             */
/*   Updated: 2021/01/27 19:37:33 by yunslee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_valid(char str[])
{
	int		i;
	int		end;
	char	*eq;

	if (ft_isdigit(str[0]) || str[0] == '=')
	{
		msg_invalid("minishell", "export", str, 1);
		return (0);
	}
	if ((eq = ft_strchr(str, '=')))
		end = eq - str;
	else
		end = ft_strlen(str);
	i = 0;
	while (i < end)
	{
		if (!ft_isalnum(str[i]) && !(str[i] == '_'))
		{
			msg_invalid("minishell", "export", str, 1);
			return (0);
		}
		i++;
	}
	return (1);
}

static void	change_value(char **envp, char argv[])
{
	if (ft_strncmp(*envp, argv, ft_strlen(argv) + 1) == '=')
		return ;
	free(*envp);
	*envp = ft_strdup(argv);
}

static int	is_exist(char *envp[], char argv[])
{
	int		i;
	int		envp_len;
	int		argv_len;
	int		ret;

	argv_len = ft_strchr(argv, '=') - argv;
	if (argv_len < 0)
		argv_len = ft_strlen(argv);
	i = 0;
	while (envp[i])
	{
		envp_len = ft_strchr(envp[i], '=') - envp[i];
		if (envp_len < 0)
			envp_len = ft_strlen(envp[i]);
		ret = ft_strncmp(envp[i], argv, argv_len + 1);
		if ((argv_len == envp_len) &&
			(ret == '=' || ret == -'=' || ret == '\0'))
			return (i);
		i++;
	}
	return (0);
}

int			execute_export(const char *path, char *const argv[],
											char *const envp[])
{
	int		i;
	int		j;

	change_argv((char **)++argv);
	if (vector_size((char **)argv))
	{
		i = 0;
		while (argv[i])
		{
			if (is_valid(argv[i]))
			{
				if ((j = is_exist((char **)envp, argv[i])))
					change_value((char **)&envp[j], argv[i]);
				else
					vector_push_back((char ***)&envp, argv[i]);
			}
			i++;
		}
	}
	else
		print_envp((char **)envp);
	get_param()->envp = (char **)envp;
	if (g_status != 256)
		g_status = 0;
	return (0);
	(void)path;
}
