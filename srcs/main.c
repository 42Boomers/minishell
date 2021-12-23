/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sylducam <sylducam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 02:18:10 by tglory            #+#    #+#             */
/*   Updated: 2021/12/23 18:33:28 by sylducam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ms_start(int ac, char **av, char **evs)
{
	t_master *master;
	int ret_code;

	master = ms_init_master(ac, av, evs);
	g_pid = -1;
	ft_sigint(&master);
	ft_sigquit(&master);
	signal(SIGINT, ((void (*)(int))ft_sigint));
	signal(SIGQUIT, ((void (*)(int))ft_sigquit));
	if (!master)
		return (1);
	// ms_register_signals(master);
	ms_cmd_register_all(master);
	if (ac > 1)
	{
		if (ft_isequals_ignore("-t", av[1]))
			ms_test_cmd(master);
		else
			ms_launch_at_start(master);
	}
	else
		ms_readline(master);
	ret_code = master->cmd_ret;
	ms_free_master(master);
	return (ret_code);
}

int main(int ac, char **av, char **evs)
{
	int ret;
	char **split;
	int size;

	// pid = getpid();						   // to delete
	// dprintf(1, "main:47 pid = %d\n", pid); // to delete
	if (ac >= 3 && !ft_strncmp(av[1], "-c", 3))
	{
		split = ft_split_ultimate(av[2], ' ');
		size = 0;
		while (split[size])
			size++;
		split--;
		av = split;
		ac = size + 1;
		exit(ms_start(ac, av, evs));
	}
	ret = 0;
	ret = ms_start(ac, av, evs);
	// dprintf(1, "main:59 pid = %d\n", pid); // to delete
	return (ret);
}
