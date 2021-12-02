/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tglory <tglory@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 02:18:10 by tglory            #+#    #+#             */
/*   Updated: 2021/12/02 19:16:15 by tglory           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int av, char **ag, char **evs)
{
	t_master	*master;

	master = ms_init_master(av, ag, evs);
	if (!master)
		return (1);
	ft_env_print_all(evs);
	(void)av;
	(void)ag;
	(void)evs;
	ms_free_master(master);
	return (0);
}
