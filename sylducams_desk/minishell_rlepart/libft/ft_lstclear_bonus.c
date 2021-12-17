/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlepart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 16:18:55 by rlepart           #+#    #+#             */
/*   Updated: 2021/01/16 16:18:56 by rlepart          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*lis;

	if (!lst || !del)
		return ;
	lis = *lst;
	while (lis)
	{
		del(lis->content);
		*lst = lis->next;
		free(lis);
		lis = *lst;
	}
	lst = 0;
}
