/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngeschwi <nathan.geschwind@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 14:51:04 by ngeschwi          #+#    #+#             */
/*   Updated: 2021/11/25 14:59:54 by ngeschwi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	close_his_pipe(t_shell *shell)
{
	if (shell->pipe_fd[shell->index][0])
		close(shell->pipe_fd[shell->index][0]);
	if (shell->pipe_fd[shell->index][1])
		close(shell->pipe_fd[shell->index][1]);
}

void	do_after_cmd(t_shell *shell)
{
	if (shell->command_list->next)
	{
		shell->command_list = shell->command_list->next;
		if (!shell->command_list->next)
		{
			if (shell->index == 2)
			{
				if (shell->pipe_fd[0][0])
					close(shell->pipe_fd[0][0]);
				if (shell->pipe_fd[0][1])
					close(shell->pipe_fd[0][1]);
			}
			else
			{
				if (shell->pipe_fd[shell->index + 1][0])
					close(shell->pipe_fd[shell->index + 1][0]);
				if (shell->pipe_fd[shell->index + 1][1])
					close(shell->pipe_fd[shell->index + 1][1]);
			}
			close_his_pipe(shell);
		}
		execute_command(shell);
	}
}
