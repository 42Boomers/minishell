/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_signal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tglory <tglory@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 09:57:19 by tglory            #+#    #+#             */
/*   Updated: 2021/12/23 22:10:27 by tglory           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ctrl_c_fork(int signum, siginfo_t *sig_info, void *ucontext_t)
{
	(void)sig_info;
	(void)ucontext_t;
	(void)signum;
	printf("\n");
	rl_replace_line("", 0);
}

static void	ctrl_c_normal(int signum, siginfo_t *sig_info, void *ucontext_t)
{
	(void)sig_info;
	(void)ucontext_t;
	(void)signum;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

static int	register_handler(int signum, void (f)(int, siginfo_t*, void*))
{
	struct sigaction	sig;

	sig.sa_flags = SA_SIGINFO;
	sig.sa_sigaction = f;
	return (sigaction(signum, &sig, NULL));
}

static int	register_signal_fork(void)
{
	return (register_handler(SIGINT, ctrl_c_fork));
}

int	register_signal_main(void)
{
	return (register_handler(SIGINT, ctrl_c_normal));
}

void	fork_created(void)
{
	register_signal_fork();
}

void	fork_deleted(void)
{
	register_signal_main();
}
