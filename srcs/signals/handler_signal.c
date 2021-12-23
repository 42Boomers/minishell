/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_signal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sylducam <sylducam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 09:57:19 by tglory            #+#    #+#             */
/*   Updated: 2021/12/23 22:34:18 by sylducam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	unlink_heredoc(void)
{
	int	fd;

	fd = 0;
	fd = open(".ms_heredoc", O_RDONLY);
	dprintf(1, "fd = %d", fd); // to delete
	if (fd)
		unlink(".ms_heredoc");
}

static void	ctrl_c_fork(int signum, siginfo_t *sig_info, void *ucontext_t)
{
	(void)sig_info;
	(void)ucontext_t;
	(void)signum;
	printf("\n");
	rl_replace_line("", 0);
	unlink_heredoc();
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
	unlink_heredoc();
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
