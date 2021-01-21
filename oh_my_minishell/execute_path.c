/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunslee <yunslee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 03:25:46 by yunslee           #+#    #+#             */
/*   Updated: 2021/01/21 16:56:34 by yunslee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	reset_getparam_by_newtrimed(void)
{
	if (get_param()->cmd_splited != NULL)
		free_split(get_param()->cmd_splited);
	get_param()->cmd_splited = ft_split(g_buf, ' ');
	if (get_param()->cmd_redirect != NULL)
		free_3d_split(get_param()->cmd_redirect);
	if (get_param()->symbol_array != NULL)
		free(get_param()->symbol_array);
	get_param()->cmd_redirect = splited_by_redirect(get_param()->cmd_splited,
								&get_param()->symbol_array);
}

static void	reset_getparam_by_macro(char **envlist, char *buff, int i)
{
	char	*temp;
	char	*new_trimed;

	ft_strlcpy(g_buf, ft_strchr(envlist[i], '=') + 1, BUFF_MAX);
	temp = ft_strchr(get_param()->cmd_trimed, ' ');
	new_trimed = ft_strjoin(g_buf, temp);
	free(get_param()->cmd_trimed);
	get_param()->cmd_trimed = new_trimed;
	parsing_redirect(get_param()->cmd_trimed);
	reset_getparam_by_newtrimed();
	check_command(get_param()->cmd_splited[0], get_param()->cmd_splited,
					get_param()->envp);
	(void)buff;
}

static void	find_macro_in_envp(char **envlist, char *buff)
{
	int i;

	i = 0;
	while (envlist[i] != NULL)
	{
		if (is_macro_in_envp(envlist[i], buff) == TRUE)
		{
			reset_getparam_by_macro(envlist, buff, i);
			break ;
		}
		i++;
	}
	ft_memset(g_buf, 0, BUFF_MAX);
}

int			execute_path(const char *path, char *const argv[],
							char *const envp[])
{
	char	buff[BUFF_MAX];
	char	*str;
	int		i;
	char	**envlist;

	i = 0;
	str = get_param()->cmd_trimed;
	envlist = get_param()->envp;
	if (path[1] == '?')
		return (command_not_found_g_status(str));
	else
	{
		copy_pathname(str, buff);
		find_macro_in_envp(envlist, buff);
	}
	return (0);
	(void)argv;
	(void)envp;
}
