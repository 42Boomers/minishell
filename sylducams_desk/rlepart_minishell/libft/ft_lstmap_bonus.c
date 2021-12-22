/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlepart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 16:19:15 by rlepart           #+#    #+#             */
/*   Updated: 2021/01/16 16:19:17 by rlepart          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*res;

	if (!lst || !f || !del || (!(res = ft_calloc(1, sizeof(*res)))))
		return (0);
	res->content = f(lst->content);
	if (!(res->next = ft_lstmap(lst->next, f, del)) && (lst->next))
	{
		del(res->content);
		res = 0;
		free(res);
		return (0);
	}
	return (res);
}
