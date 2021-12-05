/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tglory <tglory@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 02:18:10 by tglory            #+#    #+#             */
/*   Updated: 2021/12/05 04:18:46 by tglory           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_read(t_master *master)
{
	char 	*input;
	
	while (TRUE)
	{
		input = readline("minishell > ");
		if (!input)
		{
			ft_putchar('\n');
			break ;
		}
		if (ft_isequals_ignore("exit", input))
			break ;
		ms_cmd_launch(master, input, NULL, 0);
	}
	return (0);
}

int	ms_start(int av, char **ag, char **evs)
{
	t_master	*master;

	master = ms_init_master(av, ag, evs);
	if (!master)
		return (1);
	ms_cmd_register_all(master);
	if (av > 1 && ft_isequals_ignore("test", ag[1]))
		ms_test_cmd(master);
	else
		ms_read(master);
	ms_free_master(master);
	return (0);
}

int	main(int av, char **ag, char **evs)
{
	int	ret;

	ret = 0;
	ret = ms_start(av, ag, evs);
	// ret = test(av, ag, evs);
	return (ret);
}
