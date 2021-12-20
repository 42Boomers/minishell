/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tglory <tglory@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 21:24:38 by tglory            #+#    #+#             */
/*   Updated: 2021/12/20 06:32:16 by tglory           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_lstclear(void *arg)
{
	t_list	**lst;

	lst = arg;
	ft_lstclear(lst, free);
}

void	*ms_mallocw(size_t size, char *warning_message)
{
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
	{
		ft_println_red(warning_message);
		return (NULL);
	}
	return (ptr);
}

void	*ms_malloc_custom(t_list **garbage, size_t size,
		void (*free_func) (void *))
{
	void	*ptr;

	ptr = ms_mallocw(size, "Error > cannot malloc");
	ms_garbage_add(garbage, ptr, free_func);
	return (ptr);
}

void	*ms_malloc(t_list **garbage, size_t size)
{
	return (ms_malloc_custom(garbage, size, free));
}

void	*ms_malloc_master(t_master *master, size_t size)
{
	return (ms_malloc(&master->garbage, size));
}
