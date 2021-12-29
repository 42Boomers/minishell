/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstget_ignore.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblache <jblache@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 19:49:09 by jblache           #+#    #+#             */
/*   Updated: 2021/12/29 18:34:47 by jblache          ###   ########lyon.fr   */
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
