/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblache <jblache@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 11:27:55 by jblache           #+#    #+#             */
/*   Updated: 2021/12/29 18:34:47 by jblache          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f) (void *), void (del) (void *))
{
	t_list	*newlist;
	t_list	*first;

	if (f && lst && del)
	{
		first = NULL;
		while (lst)
		{
			newlist = ft_lstnew((*f)(lst->content));
			if (!newlist)
			{
				ft_lstclear(&first, del);
				return (NULL);
			}
			ft_lstadd_back(&first, newlist);
			lst = lst->next;
		}
		return (first);
	}
	return (NULL);
}
