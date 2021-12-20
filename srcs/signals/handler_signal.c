/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_signal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sylducam <sylducam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 09:57:19 by tglory            #+#    #+#             */
/*   Updated: 2021/12/20 20:48:19 by sylducam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_signal(int signum, siginfo_t *sig_info, void *ucontext_t)
{
	(void)ucontext_t;
	if (signum == 2)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
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
	int	fd;

	fd = open(".ms_heredoc", O_RDONLY);
	if (fd != -1)
	{
		unlink(".ms_heredoc");
		close(fd);
	}
	register_handler(2);
	(void)master;
}
