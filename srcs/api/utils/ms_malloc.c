/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tglory <tglory@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 21:24:38 by tglory            #+#    #+#             */
/*   Updated: 2021/12/05 01:24:50 by tglory           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_lstclear(void *arg)
{
	t_list	**lst;

	lst = arg;
	ft_lstclear(lst, free);
}

void	*ms_malloc(t_list **garbage, size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
	{
		ft_println_red("Error > cannot malloc");
		return (NULL);
	}
	ms_garbage_add(garbage, ptr, free);
	return (ptr);
}

void	*ms_malloc_master(t_master *master, size_t size)
{
	return ms_malloc(&master->free_function, size);
}
