/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_redirection_out.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngeschwi <nathan.geschwind@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 17:42:29 by ngeschwi          #+#    #+#             */
/*   Updated: 2021/11/25 16:01:01 by ngeschwi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	do_redirection_out(t_shell *shell)
{
	if (shell->pipe_fd[shell->index][0])
		close(shell->pipe_fd[shell->index][0]);
	if (shell->command_list->redirection_out == REDIRECTION_OUTPUT
		|| shell->command_list->redirection_out == REDIRECTION_DOUTPUT)
	{
		if (dup2(shell->command_list->fd_out, STDOUT_FILENO) == -1)
			ft_error_fork(shell, "Error, Bad file descriptor1");
	}
	else if (shell->command_list->next)
	{
		if (dup2(shell->pipe_fd[shell->index][1], STDOUT_FILENO) == -1)
			ft_error_fork(shell, "Error, Bad file descriptor2");
	}
	if (check_commad_2(shell) == ERROR)
	{
		if (execve(shell->command_list->program_path,
				shell->command_list->argv, shell->env) == -1)
			ft_error_fork(shell, "Error command not found");
	}
	exit(EXIT_SUCCESS);
}
