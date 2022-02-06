/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tglory <tglory@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 02:18:10 by tglory            #+#    #+#             */
/*   Updated: 2022/02/07 00:23:42 by tglory           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_start(int ac, char **av, char **evs)
{
	t_master	*master;
	int			ret_code;

	register_signal_main();
	master = ms_init_master(ac, av, evs);
	if (!master)
		return (1);
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

int	main(int ac, char **av, char **evs)
{
	int		ret;
	char	**split;
	char	*tmp;
	int		size;

	if (ac >= 3 && !ft_strncmp(av[1], "-c", 3))
	{
		tmp = malloc(ft_strlen(av[2]) * sizeof(char));
		if (!tmp)
			return (1);
		split = ft_split_ultimate(NULL, tmp, ' ');
		size = 0;
		while (split[size])
			size++;
		split--;
		av = split;
		ac = size + 1;
		exit(ms_start(ac, av, evs));
		free(tmp);
		free(av);
	}
	ret = 0;
	remove_termios_echo();
	ret = ms_start(ac, av, evs);
	return (ret);
}
