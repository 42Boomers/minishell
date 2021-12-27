/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstremove.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tglory <tglory@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 19:49:09 by tglory            #+#    #+#             */
/*   Updated: 2021/12/27 20:47:37 by tglory           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "custom.h"

static t_list	*remove(t_list *lst, char *key,
	char *(*get_key) (void *), void (*f) (void *))
{
	t_list	*temp;
	char	*str;

	if (!lst)
		return (NULL);
	str = (*get_key)(lst->content);
	if (!ft_strncmp(key, str, ft_strlen(str) + 1))
	{
		temp = lst->next;
		ft_lstdelone(lst, f);
		return (temp);
	}
	lst->next = remove(lst->next, key, get_key, f);
	return (lst);
}

void	ft_lstremove(t_list **lst, char *key,
	char *(*get_key) (void *), void (*f) (void *))
{
	*lst = remove(*lst, key, get_key, f);
}
