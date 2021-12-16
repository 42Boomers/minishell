/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tglory <tglory@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 02:18:10 by tglory            #+#    #+#             */
/*   Updated: 2021/12/16 22:41:23 by tglory           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_start(int ac, char **av, char **evs)
{
	t_master	*master;

	master = ms_init_master(ac, av, evs);
	ms_register_signals(master);
	if (!master)
		return (1);
	ms_cmd_register_all(master);
	if (ac > 1)
	{
		if (ft_isequals_ignore("test", av[1]))
			ms_test_cmd(master);
		else
			ms_launch_at_start(master);
	}
	else
		ms_readline(master);
	ms_free_master(master);
	return (0);
}

int	main(int ac, char **av, char **evs)
{
	int		ret;

	ret = 0;
	ret = ms_start(ac, av, evs);
	return (ret);
}
