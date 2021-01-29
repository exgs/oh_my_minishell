/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_path_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jikang <jikang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 03:11:30 by yunslee           #+#    #+#             */
/*   Updated: 2021/01/30 00:04:13 by jikang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		command_not_found_g_status(char *str)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putnbr_fd(g_status / 256, 2);
	ft_putendl_fd(": command not found", 2);
	g_status = 127 * 256;
	(void)str;
	return (0);
}

void	copy_pathname(char *str, char *buff)
{
	int i;

	init_array(buff);
	i = 1;
	while (str[i] != '\0' && str[i] != ' ')
	{
		buff[i - 1] = str[i];
		i++;
	}
}

int		is_macro_in_envp(const char *env_line, char *buff)
{
	if (ft_strncmp(env_line, buff, ft_strlen(buff) + 1) == '=')
		return (TRUE);
	else
		return (FALSE);
}
