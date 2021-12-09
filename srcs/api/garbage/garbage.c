/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tglory <tglory@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 00:28:11 by tglory            #+#    #+#             */
/*   Updated: 2021/12/09 01:46:40 by tglory           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_free_function	*ms_init_free_func(void	*ptr, void (*free_func) (void *))
{
	t_free_function	*garbage;

	garbage = malloc(sizeof(*garbage));
	if (!garbage)
	{
		ft_println_red("Error > An error has occured while " \
			"malloc t_free_function");
		return (NULL);
	}
	garbage->ptr = ptr;
	garbage->free_func = free_func;
	return (garbage);
}

void	ms_garbage_add(t_list **garbage, void *ptr, void (*free_func) (void *))
{
	ft_lstadd_back(garbage, ft_lstnew(ms_init_free_func(ptr, free_func)));
}

void	ms_garbage_master_add(t_master *master, void *ptr,
	void (*free_func) (void *))
{
	ms_garbage_add(&master->garbage, ptr, free_func);
}

static void	ms_free_execute_one(void *arg)
{
	t_free_function	*ff;

	ff = (t_free_function *) arg;
	ff->free_func(ff->ptr);
}

void	ms_garbage_free(t_list **garbage)
{
	if (garbage)
	{
		ft_lstiter(*garbage, ms_free_execute_one);
		ft_lstclear(garbage, free);
	}
}
