/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir_lst.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-kada <mel-kada@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/26 17:27:17 by mel-kada          #+#    #+#             */
/*   Updated: 2021/03/03 21:30:50 by mel-kada         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_redir_lst	*ft_redir_lst_new(char *name, int type)
{
	t_redir_lst	*new;

	new = malloc(sizeof(t_redir_lst));
	if (!new)
		return (NULL);
	new->filename = name;
	new->type = type;
	new->next = NULL;
	return (new);
}

t_redir_lst	*ft_redir_lst_last(t_redir_lst *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void		ft_redir_lst_add(t_redir_lst **lst, t_redir_lst *elem)
{
	t_redir_lst	*ptr;

	if (!*lst)
		*lst = elem;
	ptr = ft_redir_lst_last(*lst);
	if (ptr && elem)
	{
		ptr->next = elem;
		elem->next = NULL;
	}
}

void		ft_redir_lst_clear(t_redir_lst *lst)
{
	t_redir_lst	*ptr;

	ptr = NULL;
	while (lst)
	{
		ptr = lst->next;
		free(lst->filename);
		free(lst);
		lst = ptr;
	}
}
