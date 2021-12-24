/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_signal2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tglory <tglory@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 09:57:19 by tglory            #+#    #+#             */
/*   Updated: 2021/12/24 16:42:46 by tglory           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	register_handler(int signum, void (f)(int, siginfo_t*, void*))
{
	struct sigaction	sig;

	sig.sa_flags = SA_SIGINFO;
	sig.sa_sigaction = f;
	return (sigaction(signum, &sig, NULL));
}

void	register_signal_fork(void)
{
	register_handler(SIGQUIT, ctrl_bs_fork);
	register_handler(SIGINT, ctrl_c_fork);
}

void	register_signal_main(void)
{
	register_handler(SIGQUIT, ctrl_bs_normal);
	register_handler(SIGINT, ctrl_c_normal);
}
