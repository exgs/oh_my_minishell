/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunslee <yunslee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/09 01:23:44 by yunslee           #+#    #+#             */
/*   Updated: 2021/01/01 17:13:21 by yunslee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list *temp;
	t_list *curr;

	if (lst == 0)
		return ;
	curr = *lst;
	while (curr != NULL)
	{
		temp = curr;
		curr = curr->next;
		if (del != NULL)
			del(temp->content);
		free(temp);
	}
	*lst = NULL;
}
