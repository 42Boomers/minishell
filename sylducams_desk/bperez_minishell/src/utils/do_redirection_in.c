/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_redirection_in.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngeschwi <nathan.geschwind@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 17:39:09 by ngeschwi          #+#    #+#             */
/*   Updated: 2021/11/25 16:04:00 by ngeschwi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	do_redirection_if_prev(t_shell *shell)
{
	if (shell->command_list->prev)
	{
		if (shell->index == 0)
		{
			if (dup2(shell->pipe_fd[2][0], STDIN_FILENO) == -1)
				ft_error_fork(shell, "Error, Bad file descriptor");
		}
		else
			if (dup2(shell->pipe_fd[shell->index - 1][0], STDIN_FILENO) == -1)
				ft_error_fork(shell, "Error, Bad file descriptor");
	}
}

void	do_redirection_in(t_shell *shell)
{
	g_process_section = 2;
	if (shell->index == 0)
	{
		if (shell->pipe_fd[2][1])
			close(shell->pipe_fd[2][1]);
	}
	else
		if (shell->pipe_fd[shell->index - 1][1])
			close(shell->pipe_fd[shell->index - 1][1]);
	if (shell->command_list->redirection_in == REDIRECTION_INPUT)
	{
		if (dup2(shell->command_list->fd_in, STDIN_FILENO) == -1)
			ft_error_fork(shell, "Error, Bad file descriptor");
	}
	else if (shell->command_list->redirection_in == REDIRECTION_DINPUT)
	{
		if (dup2(shell->pipe_fd_redi_din[0], STDIN_FILENO) == -1)
			ft_error_fork(shell, "Error, Bad file descriptor");
	}
	do_redirection_if_prev(shell);
	do_redirection_out(shell);
}
