/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_signal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tglory <tglory@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 09:57:19 by tglory            #+#    #+#             */
/*   Updated: 2021/12/10 23:45:48 by tglory           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_signal(int signum, siginfo_t *sig_info, void *ucontext_t)
{
	(void)ucontext_t;
	if (signum == 2)
	{
		rl_redisplay();
		printf("\n\e[36mminishell DEBUG > \e[96m");
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

void	ms_register_signals(t_master *master)
{
	// int	i;

	// i = 0;
	// while (i <= 60)
	// 	register_handler(i++);
	register_handler(2);
	(void)master;
}
