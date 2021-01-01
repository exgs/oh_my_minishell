/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunslee <yunslee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/09 01:32:50 by yunslee           #+#    #+#             */
/*   Updated: 2021/01/01 17:20:59 by yunslee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	lst_reset(t_list **lst, void (*del)(void *))
{
	t_list *curr;

	curr = *lst;
	while (lst != NULL)
	{
		*lst = (*lst)->next;
		if (del != NULL)
			del(curr->content);
		free(curr);
		curr = *lst;
	}
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*new_curr;
	t_list	*curr;

	if (lst == NULL || f == NULL)
		return (NULL);
	if (NULL == (new = (t_list *)malloc(sizeof(t_list) * 1)))
		return (NULL);
	new->content = f(lst->content);
	curr = lst->next;
	new_curr = new;
	while (curr != NULL)
	{
		if (NULL == (new_curr->next = (t_list *)malloc(sizeof(t_list) * 1)))
		{
			lst_reset(&new, del);
			return (NULL);
		}
		new_curr = new_curr->next;
		new_curr->content = f(curr->content);
		curr = curr->next;
	}
	new_curr->next = NULL;
	return (new);
}
