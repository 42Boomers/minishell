/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstget_ignore.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tglory <tglory@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 19:49:09 by tglory            #+#    #+#             */
/*   Updated: 2021/12/20 07:33:33 by tglory           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "custom.h"

void	*ft_lstget_ignore(t_list *lst, char *key, char *(*get_key) (void *))
{
	char	*str;

	if (lst && get_key)
	{
		while (lst)
		{
			str = (*get_key)(lst->content);
			if (ft_isequals_ignore(key, str))
			{
				return (lst->content);
			}
			lst = lst->next;
		}
	}
	return (NULL);
}
