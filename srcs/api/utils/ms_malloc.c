/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tglory <tglory@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 21:24:38 by tglory            #+#    #+#             */
/*   Updated: 2021/12/02 23:18:15 by tglory           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_lstclear(void *arg)
{
	t_list **lst;

	lst = arg;
	ft_lstclear(lst, free);
}

void	*ms_malloc(t_master *master, size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
	{
		ft_println_red("Error : cannot malloc");
		return (NULL);
	}
	ms_free_f_add(master, ptr, free);
	return (ptr);
}
