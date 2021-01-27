/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_commands_from_gnl.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jikang <jikang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 23:06:37 by jikang            #+#    #+#             */
/*   Updated: 2021/01/23 02:05:22 by jikang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		del(void *content)
{
	free(content);
}

void		get_commands_from_gnl(t_list **cmd, char *line)
{
	char	*substr;
	t_list	*new;
	int		i;

	if (check_semicolon(line) == -1)
		return ;
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
