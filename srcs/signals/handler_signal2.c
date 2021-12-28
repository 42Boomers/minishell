/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_signal2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tglory <tglory@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 09:57:19 by tglory            #+#    #+#             */
/*   Updated: 2021/12/28 15:28:31 by tglory           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	register_handler(int signum, void (f)(int, siginfo_t *, void *))
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

void	termios_restore(struct termios *term)
{
	static struct termios	*saved;

	if (!saved)
	{
		saved = term;
		return ;
	}
	tcsetattr(STDIN_FILENO, TCSANOW, saved);
}

void	remove_termios_echo(void)
{
	int				rc;
	struct termios	*saved;
	struct termios	attributes;

	saved = ms_mallocw(sizeof(*saved), "Cannot malloc termios");
	if (!saved)
		return ;
	rc = tcgetattr(STDIN_FILENO, saved);
	if (rc)
	{
		perror("tcgetattr");
		exit(1);
	}
	termios_restore(saved);
	tcgetattr(STDIN_FILENO, &attributes);
	attributes.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &attributes);
}
