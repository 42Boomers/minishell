/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngeschwi <nathan.geschwind@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 15:10:56 by ngeschwi          #+#    #+#             */
/*   Updated: 2021/11/25 12:05:40 by ngeschwi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_have_to_print(char *line_env)
{
	int	i;
	int	check;

	i = 0;
	check = 0;
	while (line_env[i])
	{
		if (line_env[i] == '=')
			check = 1;
		i++;
	}
	return (check);
}

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

int	ft_env(t_shell *shell)
{
	int		i;
	char	*str;
	char	*save;

	i = 0;
	str = NULL;
	save = NULL;
	do_redirection(shell);
	while (shell->env[i])
	{
		if (check_have_to_print(shell->env[i]))
		{
			save = ft_strjoin(str, shell->env[i]);
			str = ft_strjoin(save, "\n");
			free(save);
			save = NULL;
		}
		i++;
	}
	write(shell->pipe_fd[shell->index][1], str, ft_strlen(str));
	if (shell->pipe_fd[shell->index][1])
		close(shell->pipe_fd[shell->index][1]);
	free(str);
	return (SUCCESS);
}
