/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tglory <tglory@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 02:18:10 by tglory            #+#    #+#             */
/*   Updated: 2021/12/05 05:32:29 by tglory           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_read(t_master *master)
{
	char 	*input;
	char 	**raw_args;
	char 	**args;
	int		i;
	
	input = NULL;
	while (TRUE)
	{
		input = readline("minishell > ");
		if (!input)
		{
			ft_putchar('\n');
			break ;
		}
		if (!*input)
		{
			free(input);
			continue;
		}
		add_history(input);
		if (ft_isequals_ignore("exit", input))
		{
			printf("\e[34mBye\e[0m\n");
			break ;
		}
		raw_args = ft_split(input, ' ');
		if (raw_args && raw_args[0])
		{
			ms_garbage_default_add(master, raw_args, free);
			i = 0;
			while (raw_args[i])
				ms_garbage_default_add(master, raw_args[i++], free);
			args = raw_args;
			args++;
			ms_cmd_launch(master, raw_args[0], args, i - 1);
		}
		else
		{
			ms_cmd_launch(master, input, NULL, 0);
			if (raw_args)
				free(raw_args);
		}
		free(input);
	}
	if (input)
		free(input);
	return (0);
}

int	ms_start(int av, char **ag, char **evs)
{
	t_master	*master;

	master = ms_init_master(av, ag, evs);
	if (!master)
		return (1);
	ms_cmd_register_all(master);
	if (av > 2)
		ms_launch_at_start(master);
	else if (av > 1 && ft_isequals_ignore("test", ag[1]))
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
