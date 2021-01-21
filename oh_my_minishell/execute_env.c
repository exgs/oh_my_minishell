/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jikang <jikang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 05:17:12 by ykoh              #+#    #+#             */
/*   Updated: 2021/01/21 15:04:09 by jikang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	(void)argv;
}

int			execute_env(const char *path,
						char *const argv[], char *const envp[])
{
	int		i;
	int		j;

	if (argv[1])
		return (msg_error("minishell", "env", argv[1], 2));
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
