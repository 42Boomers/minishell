/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: neben <neben@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 12:24:48 by ngeschwi          #+#    #+#             */
/*   Updated: 2021/11/29 13:21:49 by neben            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	do_redirection(t_shell *shell)
{
	if (shell->command_list->redirection_out == 2)
	{
		if (shell->pipe_fd[shell->index][0])
			close(shell->pipe_fd[shell->index][0]);
		if (dup2(shell->command_list->fd_out,
				shell->pipe_fd[shell->index][1]) == -1)
			ft_error_fork(shell, "Error, dup2");
	}
	else if (!shell->command_list->next)
	{
		if (shell->pipe_fd[shell->index][0])
			close(shell->pipe_fd[shell->index][0]);
		if (dup2(1, shell->pipe_fd[shell->index][1]) == -1)
			ft_error_fork(shell, "Error dup2 cmd");
	}
}

static void	check_n_option(t_shell *shell, int *i, int *check)
{
	if (shell->command_list->argv[1]
		|| ft_strlen(shell->command_list->argv[1]) > 0)
	{
		if (!ft_strcmp(shell->command_list->argv[1], "-n"))
		{
			*i += 1;
			*check += 1;
		}
	}
}

int	ft_echo(t_shell *shell)
{
	int	i;
	int	check;

	i = 0;
	check = 0;
	do_redirection(shell);
	check_n_option(shell, &i, &check);
	i++;
	while (shell->command_list->argv[i]
		|| ft_strlen(shell->command_list->argv[i]) > 0)
	{
		if (shell->command_list->argv[i + 1])
			shell->command_list->argv[i]
				= ft_strjoin(shell->command_list->argv[i], " ");
		write(shell->pipe_fd[shell->index][1], shell->command_list->argv[i],
			ft_strlen(shell->command_list->argv[i]));
		i++;
	}
	if (check == 0)
		write(shell->pipe_fd[shell->index][1], "\n", 1);
	if (shell->pipe_fd[shell->index][1])
		close(shell->pipe_fd[shell->index][1]);
	return (SUCCESS);
}
