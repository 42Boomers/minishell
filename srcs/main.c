/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sylducam <sylducam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 02:18:10 by tglory            #+#    #+#             */
/*   Updated: 2021/12/07 15:45:50 by sylducam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_start(int av, char **ag, char **evs)
{
	t_master	*master;

	master = ms_init_master(av, ag, evs);
	ms_register_signals(master);
	if (!master)
		return (1);
	ms_cmd_register_all(master);
	if (av > 1)
	{
		if (ft_isequals_ignore("test", ag[1]))
			ms_test_cmd(master);
		else
			ms_launch_at_start(master);
	}
	else
		ms_readline(master);
	ms_free_master(master);
	return (0);
}

int	main(int av, char **ag, char **evs) // syl : pourquoi argc devient av et argv devient ag ? c = count et v = value, non ?
{
	int		ret;
	// static pid_t	other_pid;
	// pid_t	pid;

	ret = 0;
	ret = ms_start(av, ag, evs);
	// ret = test(av, ag, evs);
	// other_pid = -1;
	// pid = fork();
	// other_pid = pid;
	// printf("PID fork %d - %d\n", pid, other_pid);
	// if (!pid)
	// {
		//waitpid();
	// } else {
	// 	usleep(pid * 1000);
	// }
	// execve("/bin/date", ag, evs);
	// getcwd() -> pour cd
	return (ret);
}
