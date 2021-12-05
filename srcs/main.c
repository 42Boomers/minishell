/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tglory <tglory@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 02:18:10 by tglory            #+#    #+#             */
/*   Updated: 2021/12/05 01:26:47 by tglory           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_launch_at_start(t_master *master, int av, char **ag)
{
	char	*command;
	char	**args;

	if (av <= 1)
		return (1);
	command = *++ag;
	args = NULL;
	if (av > 2)
	{
		ag++;
		args = ag;
	}
	ms_cmd_launch(master, command, args, av - 1);
	return (0);
}

int	main(int av, char **ag, char **evs)
{
	t_master	*master;

	master = ms_init_master(av, ag, evs);
	if (!master)
		return (1);
	ms_cmd_register_all(master);
	//ms_launch_at_start(master, av, ag);
	ms_cmd_launch(master, "env", NULL, 0);
	ms_free_master(master);
	return (0);
}
