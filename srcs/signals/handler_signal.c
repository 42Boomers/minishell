/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_signal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sylducam <sylducam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 09:57:19 by tglory            #+#    #+#             */
/*   Updated: 2021/12/18 13:00:54 by sylducam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_signal(int signum, siginfo_t *sig_info, void *ucontext_t)
{
	(void)ucontext_t;
	if (signum == SIGINT)
	{
		rl_redisplay(); // etudie la fonction. est elle autoriser?
		printf("\n\e[36mminishell DEBUG > \e[96m");//retour a zero du readline
	}
	else
		printf("DEBUG SIGNAL %d - from PID %d\n", sig_info->si_signo, sig_info->si_pid);
}

static int	register_handler(int signum)
{
	struct sigaction	sig;

	sig.sa_flags = SA_SIGINFO;
	sig.sa_sigaction = handle_signal;
	return (sigaction(signum, &sig, NULL));
}

void	ms_register_signals(int signal, t_master *master)
{
	static t_master	*save = NULL;

	signal = 0;
	dprintf(1, "pid = %d\n", master->pid); // del
	if (!save)
		save = master;
	else
	{
		write(1, "\n", 1);
		if (save->pid == -1)
		{
			ft_putstr_fd("pid = -1\n", 2);
			ft_putstr_fd("minishell -> ", 1);
		}
		else if (save->pid)
		{
			ft_putstr_fd("positive pid\n", 2);
			kill(save->pid, SIGINT);
		}
		else
			ft_putstr_fd("pid = 0\n", 2);
	}
	// int	i;

	// i = 0;
	// while (i <= 60)
	// 	register_handler(i++);
	register_handler(2);
	(void)master;
}

// void	ms_register_signals(t_master *master)
// {
// 	// int	i;

// 	// i = 0;
// 	// while (i <= 60)
// 	// 	register_handler(i++);
// 	register_handler(2);
// 	(void)master;
// }
