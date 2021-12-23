/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_signal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sylducam <sylducam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 09:57:19 by tglory            #+#    #+#             */
/*   Updated: 2021/12/23 16:07:08 by sylducam         ###   ########.fr       */
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
	else if (save->pid > 0)
	{
		dprintf(1, "\nsyltest pid > 0\n"); // to delete
		g_ctrl_c = 1;
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

	if (!save)
		save = master;
	else
	{
		if (save->pid == -1)
		{
			dprintf(1, "\nsyltest pid == -1\n"); // to delete
			printf("\n");
			g_ctrl_c = 1;
			// rl_on_new_line();
			rl_replace_line("", 0);
			// rl_redisplay();
			// ms_readline(master);
			// ft_putstr_fd("minishell -> ", 1);
		}
		if (save->pid)
		{
			dprintf(1, "\nsyltest pid > -1\n"); // to delete
			kill(save->pid, SIGINT);
			g_ctrl_c = 1;
			dprintf(1, "\nX syltest g_ctrl_c = %d\n", g_ctrl_c); // to delete
			printf("\n");
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
		}
	}
}

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
