/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_commands_from_gnl.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jikang <jikang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 23:06:37 by jikang            #+#    #+#             */
/*   Updated: 2021/01/21 02:07:16 by jikang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		del(void *content)
{
	free(content);
}

char		*ft_strstr(const char *haystack, const char *needle)
{
	size_t	i;
	size_t	k;

	i = 0;
	if (needle[i] == 0)
		return ((char *)haystack);
	while (haystack[i])
	{
		k = 0;
		while (haystack[i + k] == needle[k] && haystack[i + k])
		{
			if (needle[k + 1] == 0)
				return ((char *)&haystack[i]);
			++k;
		}
		++i;
	}
	return (0);
}

char		*ft_strsep(char **command, const char *delim)
{
	char	*init_str;
	char	*command_index;

	command_index = NULL;
	if (*command == NULL)
		return (NULL);
	if ((*command)[0] == '\0')
		return (NULL);
	init_str = *command;
	command_index = ft_strstr(*command, delim);
	while (delim && *delim && command_index && *command_index)
	{
		*command_index = '\0';
		++command_index;
		++delim;
	}
	*command = command_index;
	return (init_str);
}

void		get_commands_from_gnl(t_list **cmd, char *line)
{
	char	*substr;
	t_list	*new;
	int		i;

	check_semicolon(line);
	i = 0;
	while (TRUE)
	{
		substr = ft_strsemi(&line, get_param()->semi_arr, i);
		if (substr == NULL)
			break ;
		if (ft_strlen(substr) == 0)
			continue ;
		new = ft_lstnew(substr);
		new->split_by_pipes = split_pipe(substr);
		unseal_firstquotes(new->split_by_pipes);
		ft_lstadd_back(cmd, new);
		i++;
	}
}
