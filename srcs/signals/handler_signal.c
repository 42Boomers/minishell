/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_signal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sylducam <sylducam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 09:57:19 by tglory            #+#    #+#             */
/*   Updated: 2021/12/22 12:38:27 by sylducam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "minishell.h"

// static void	ctrl_c_fork(void)
// {
// }
// static void	ctrl_c_normal(void)
// {
// }

static void	handle_signal(int signum, siginfo_t *sig_info, void *ucontext_t)
{
	(void)sig_info;
	(void)ucontext_t;
/* understand diffrent behaviours of ctrl-c depending on minishell being in
- "normal" mode
- having created a fork but not being in it
- being inside a fork
>>> try all the different functions (rl_on_new_line, rl_replace_line and
rl_redisplay) but forsti of all, try and understand theoritically, what's
minishell in a minishell is supposed to do.
What to do after the whole action of ctrl-c had been performed ?
Should I change the value of g_ctrl_c ?
*/
	if (signum == SIGINT)
	{
		if (g_ctrl_c == 0)
		{
			// ctrl_c_normal();
			printf("\n");
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
		}
		else if (g_ctrl_c == 1)
		{
			// ctrl_c_fork();
			printf("\n");
			rl_on_new_line();
			rl_replace_line("", 0);
			g_ctrl_c = 0;
		}
		else if (g_ctrl_c == 2)
		{
			printf("\n");
			rl_on_new_line();
			rl_replace_line("", 0);
		}
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
	int	fd;								//
										//
	fd = open(".ms_heredoc", O_RDONLY); // syl:toute cette partie sur ms_heredoc
	if (fd != -1)						// est a revoir, Max dit qu'elle n'est
	{									// pas bonne. Voir avec lui.
		unlink(".ms_heredoc");			//
		close(fd);						//
	}
	register_handler(SIGINT);
	(void)master;
}
