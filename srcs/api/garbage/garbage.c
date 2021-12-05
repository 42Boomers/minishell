/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tglory <tglory@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 00:28:11 by tglory            #+#    #+#             */
/*   Updated: 2021/12/05 01:28:37 by tglory           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_free_function	*ms_init_free_func(void	*ptr, void (*free_func) (void *))
{
	t_free_function	*free_function;

	free_function = malloc(sizeof(*free_function));
	if (!free_function)
	{
		ft_println_red("Error > An error has occured while malloc t_free_function");
		return (NULL);
	}
	free_function->ptr = ptr;
	free_function->free_func = free_func;
	return (free_function);
}

void	ms_garbage_add(t_list **garbage, void *ptr, void (*free_func) (void *))
{
	ft_lstadd_back(garbage, ft_lstnew(ms_init_free_func(ptr, free_func)));
}

void	ms_garbage_default_add(t_master *master, void *ptr, void (*free_func) (void *))
{
	ms_garbage_add(&master->free_function, ptr, free_func);
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

void	ms_free_master(t_master	*master)
{
	ms_garbage_free(&master->free_function);
	free(master->cmds);
	free(master);
}

// t_garbage	*ms_init_garbage(char *(*get_key)(void *), void (*free_func) (void *))
// {
// 	t_garbage	*garbage;

// 	garbage = malloc(sizeof(*garbage));
// 	if (!garbage)
// 	{
// 		ft_println_red("Error > An error has occured while malloc garbage");
// 		return (NULL);
// 	}
// 	garbage->get_key = get_key;
// 	garbage->free_func = free_func;
// 	return (garbage);
// }
