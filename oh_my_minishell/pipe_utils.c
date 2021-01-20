/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunslee <yunslee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 01:02:05 by yunslee           #+#    #+#             */
/*   Updated: 2021/01/21 01:39:31 by yunslee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*string_tolower(char *str)
{
	int i;

	if (str == NULL)
		return (NULL);
	i = 0;
	while (str[i])
	{
		str[i] = ft_tolower(str[i]);
		i++;
	}
	return (str);
}

int		which_command(char *cmd)
{
	if (cmd == NULL)
		return (-1);
	if (!ft_strncmp(string_tolower(cmd), "ls", 10))
		return (LS);
	if (!ft_strncmp(string_tolower(cmd), "/bin/ls", 10))
		return (LS);
	if (!ft_strncmp(string_tolower(cmd), "grep", 10))
		return (GREP);
	if (!ft_strncmp(string_tolower(cmd), "/usr/bin/grep", 15))
		return (GREP);
	if (!ft_strncmp(string_tolower(cmd), "clear", 10))
		return (CLEAR);
	if (!ft_strncmp(string_tolower(cmd), "/usr/bin/clear", 15))
		return (CLEAR);
	if (!ft_strncmp(string_tolower(cmd), "cat", 10))
		return (CAT);
	if (!ft_strncmp(string_tolower(cmd), "/bin/cat", 15))
		return (CAT);
	else
		return (-1);
}

int		need_redirection(void)
{
	int i;

	i = 0;
	while (get_param()->symbol_array[i] != 0)
	{
		if (get_param()->symbol_array[i] == -1)
			return (ERROR);
		i++;
	}
	if (get_param()->symbol_array[0] == 0)
		return (FALSE);
	else
		return (TRUE);
}
