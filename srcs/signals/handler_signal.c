/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_signal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tglory <tglory@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 09:57:19 by tglory            #+#    #+#             */
/*   Updated: 2021/12/28 16:09:10 by tglory           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	unlink_heredoc(void)
{
	unlink(".ms_heredoc");
}

void	ctrl_c_fork(int signum, siginfo_t *sig_info, void *ucontext_t)
{
	(void)sig_info;
	(void)ucontext_t;
	(void)signum;
	printf("\n");
	rl_replace_line("", 0);
	unlink_heredoc();
}

void	ctrl_c_normal(int signum, siginfo_t *sig_info, void *ucontext_t)
{
	(void)sig_info;
	(void)ucontext_t;
	(void)signum;
	printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	unlink_heredoc();
}

void	ctrl_bs_normal(int signum, siginfo_t *sig_info, void *ucontext_t)
{
	(void)sig_info;
	(void)ucontext_t;
	(void)signum;
}

void	ctrl_bs_fork(int signum, siginfo_t *sig_info, void *ucontext_t)
{
	printf("^\\Quit: 3\n");
	(void)sig_info;
	(void)ucontext_t;
	(void)signum;
}
