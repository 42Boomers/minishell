/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_signal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sylducam <sylducam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 09:57:19 by tglory            #+#    #+#             */
/*   Updated: 2021/12/23 19:17:26 by sylducam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*------------------------------------------------------------------------------
version inspired from rlepart
------------------------------------------------------------------------------*/

void ft_sigquit(void *master)
{
	static t_master *save = NULL;

	if (!save)
		save = master;
	// else if (save->pid > 0)
	else if (g_ctrl_c == 0)
	{
		dprintf(1, "Z\n"); // to delete
		// g_ctrl_c = 1; // keep it ?
		kill(save->pid, SIGQUIT);
		printf("\n");
		// rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		ft_putstr_fd("Quit : 3\n", 1);
	}
}

void ft_sigint(void *master)
{
	static t_master *save = NULL;

	// if (!save)
	// // // 	save = master;
	// // else
	// {
		// if (save->pid == -1)
		if (g_ctrl_c == 0)
		{
			dprintf(1, "X\n"); // to delete
			printf("\n");
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
		}
		if (g_ctrl_c == 1)
		{
			dprintf(1, "Y\n"); // to delete
			kill(save->pid, SIGINT);
			// g_ctrl_c = 1;
			printf("\n");
			rl_on_new_line();
			rl_replace_line("", 0);
			dprintf(1, "handler_signal.c:62 g_ctrl_c = %d\n", g_ctrl_c); // to delete
			// if (g_ctrl_c == 0)
				rl_redisplay();
		}
	// }
}

/*------------------------------------------------------------------------------
my old version
------------------------------------------------------------------------------*/

// static void	ctrl_c_fork(void)
// {
// }
// static void	ctrl_c_normal(void)
// {
// }

// static void	handle_signal(int signum, siginfo_t *sig_info, void *ucontext_t)
// {
// 	(void)sig_info;
// 	(void)ucontext_t;
// /* understand diffrent behaviours of ctrl-c depending on minishell being in
// - "normal" mode
// - having created a fork but not being in it
// - being inside a fork
// >>> try all the different functions (rl_on_new_line, rl_replace_line and
// rl_redisplay) but forsti of all, try and understand theoritically, what's
// minishell in a minishell is supposed to do.
// What to do after the whole action of ctrl-c had been performed ?
// Should I change the value of g_ctrl_c ?
// */
// 	if (signum == SIGINT)
// 	{
// 		if (g_ctrl_c == 0)
// 		{
// 			// ctrl_c_normal();
// 			printf("\n");
// 			rl_on_new_line();
// 			rl_replace_line("", 0);
// 			rl_redisplay();
// 		}
// 		else if (g_ctrl_c == 1)
// 		{
// 			// ctrl_c_fork();
// 			printf("\n");
// 			rl_on_new_line();
// 			rl_replace_line("", 0);
// 			g_ctrl_c = 0;
// 		}
// 		else if (g_ctrl_c == 2)
// 		{
// 			printf("\n");
// 			rl_on_new_line();
// 			rl_replace_line("", 0);
// 		}

/*------------------------------------------------------------------------------
version without segfault
------------------------------------------------------------------------------*/

// static void	ctrl_c_fork(void)
// {
// }
// static void	ctrl_c_normal(void)
// {
// }

// static void	ctrl_c_fork(void)
// {
// 	printf("\n");
// 	rl_on_new_line();
// 	rl_replace_line("", 0);
// 	g_ctrl_c = 0;
// }

// static void	ctrl_c_normal(void)
// {
// 	printf("\n");
// 	rl_on_new_line();
// 	rl_replace_line("", 0);
// 	rl_redisplay();
// }

// static void	handle_signal(int signum, siginfo_t *sig_info, void *ucontext_t)
// {
// 	(void)sig_info;
// 	(void)ucontext_t;
// 	if (signum == SIGINT)
// 	{
// 		if (g_ctrl_c == 0)
// 			ctrl_c_normal();
// 		if (g_ctrl_c == 1)
// 			ctrl_c_fork();
// 	}
// }

// static int	register_handler(int signum)
// {
// 	struct sigaction	sig;

// 	sig.sa_flags = SA_SIGINFO;
// 	sig.sa_sigaction = handle_signal;
// 	return (sigaction(signum, &sig, NULL));
// }

// void	ms_register_signals(t_master *master)
// {
// 	int	fd;								//
// 										//
// 	fd = open(".ms_heredoc", O_RDONLY); // syl:toute cette partie sur ms_heredoc
// 	if (fd != -1)						// est a revoir, Max dit qu'elle n'est
// 	{									// pas bonne. Voir avec lui.
// 		unlink(".ms_heredoc");			//
// 		close(fd);						//
// 	}
// 	register_handler(SIGINT);
// 	(void)master;
// }

/*------------------------------------------------------------------------------
version work in progress
------------------------------------------------------------------------------*/

// utilises signal au lieu de sigaction ? Prends exemple sur rlepart, je crois
// kill toujours pas gere

// static void	ctrl_c_fork(void)
// {
// 	printf("\n");
// 	rl_on_new_line();
// 	rl_replace_line("", 0);
// 	g_ctrl_c = 0;
// }

// static void	ctrl_c_normal(void)
// {
// 	printf("\n");
// 	rl_on_new_line();
// 	rl_replace_line("", 0);
// 	rl_redisplay();
// }

// static void	handle_signal(int signum, siginfo_t *sig_info, void *our_master)
// {
// 	(void)sig_info;
// 	(void)signum;
// 	t_master *master;

// 	master = our_master;
// 	// if (signum == SIGINT)
// 	if (master->signum == SIGINT)
// 	{
// 		// printf("\n");
// 		printf("%s", ms_prefix_get(master));
// 		// ms_readline()
// 		// if (g_ctrl_c == 0)
// 			// ctrl_c_normal();
// 		// if (g_ctrl_c == 1)
// 			// ctrl_c_fork();
// 	}
// }

// static int	register_handler(t_master *master)
// {
// 	struct sigaction	sig;

// 	sig.sa_flags = SA_SIGINFO;
// 	sig.sa_sigaction = handle_signal;
// 	return (sigaction(SIGINT, &sig, master));
// }

// void	ms_register_signals(t_master *master)
// {
// 	int	fd;								//
// 										//
// 	fd = open(".ms_heredoc", O_RDONLY); // syl:toute cette partie sur ms_heredoc
// 	if (fd != -1)						// est a revoir, Max dit qu'elle n'est
// 	{									// pas bonne. Voir avec lui.
// 		unlink(".ms_heredoc");			//
// 		close(fd);						//
// 	}
// 	register_handler(master);
// 	// if (master->signum == SIGINT)
// 	// 	printf("%s", ms_prefix_get(master));
// 	(void)master;
// }
