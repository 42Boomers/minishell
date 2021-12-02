/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   master_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tglory <tglory@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 18:35:32 by tglory            #+#    #+#             */
/*   Updated: 2021/12/02 23:35:11 by tglory           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_free_function	*ms_init_free_func(void	*ptr, void (*free_func) (void *))
{
	t_free_function	*free_function;

	free_function = malloc(sizeof(t_free_function));
	if (!free_function)
	{
		ft_println_red("Error > An error has occured while malloc t_free_function");
		return (NULL);
	}
	free_function->ptr = ptr;
	free_function->free_func = free_func;
	return (free_function);
}

void	ms_free_f_add(t_master *master, void *ptr, void (*free_func) (void *))
{
	ft_lstadd_back(&(master->free_function), ft_lstnew(ms_init_free_func(ptr, free_func)));
}

t_master	*ms_init_master(int av, char **ag, char **ev)
{
	t_master	*master;

	master = malloc(sizeof(t_master));
	if (!master)
	{
		ft_println_red("Error > An error has occured while malloc t_master");
		return (NULL);
	}
	master->free_function = NULL;
	master->cmds = NULL;
	master->envs = ev;
	(void)av;
	(void)ag;
	(void)ev;
	return (master);
}

void	ms_free_execute_one(void *arg)
{
	t_free_function	*ff;

	ff = (t_free_function *) arg;
	ff->free_func(ff->ptr);
}

void	ms_free_master(t_master	*master)
{
	if (master->free_function)
	{
		ft_lstiter(master->free_function, ms_free_execute_one);
		ft_lstclear(&master->free_function, free);
		ft_lstclear(&master->cmds, free);
	}
	free(master);
}
