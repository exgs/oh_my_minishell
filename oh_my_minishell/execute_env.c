/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykoh <ykoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 01:49:01 by ykoh              #+#    #+#             */
/*   Updated: 2021/01/17 01:49:04 by ykoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	msg_incorrect(char *arg)
{
	ft_putstr_fd("bash: env: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd("incorrect usage", 2);
	ft_putendl_fd("usage: env without any options and any arguments", 2);
	g_status = 2 * 256;
	return (-1);
}

static void	export_env_path(const char *path,
							char *const argv[], char *const envp[])
{
	char	*tmp[3];

	tmp[0] = "export";
	if (ft_strncmp(path, "env", 4) == '\0')
		tmp[1] = ft_strjoin("_=", "/usr/bin/env");
	else
		tmp[1] = ft_strjoin("_=", path);
	tmp[2] = NULL;
	execute_export(path, tmp, envp);
	free(tmp[1]);
}

int			execute_env(const char *path,
						char *const argv[], char *const envp[])
{
	int		i;
	int		j;
	char	**tmp;

	if (argv[1])
		return (msg_incorrect(argv[1]));
	export_env_path(path, argv, get_param()->envp);
	i = 0;
	while (envp[i])
	{
		if (ft_strchr(envp[i], '='))
		{
			if (ft_strncmp(envp[i], "_=", 2) == '\0')
			{
				j = i++;
				continue;
			}
			ft_putendl_fd(envp[i], 1);
		}
		i++;
	}
	ft_putendl_fd(envp[j], 1);
	g_status = 0;
	return (0);
}
