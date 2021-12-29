/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_fork.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblache <jblache@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 13:04:22 by mrozniec          #+#    #+#             */
/*   Updated: 2021/12/29 15:09:55 by jblache          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_error_pipe(int pip_end[2])
{
	if (pipe(pip_end) == -1)
	{
		ft_println_red("Error > An error has occured while pipe creation");
		return (-1);
	}
	return (0);
}

void	ms_check_redir(char **command, char **args)
{
	char	*temp;

	temp = NULL;
	if (command && args[0] != NULL && args[1] != NULL && \
	!ft_isequals(args[1], "<") && !ft_isequals(args[1], "<<") && \
	!ft_isequals(args[1], ">") && !ft_isequals(args[1], ">>") && \
	!ft_isequals(args[1], "|"))
	{
		if ((ft_strcmp(*command, "<") == 0) || \
		(ft_strcmp(*command, "<<") == 0) || \
		(ft_strcmp(*command, ">") == 0) || (ft_strcmp(*command, ">>") == 0))
		{
			temp = *command;
			*command = args[1];
			args[1] = args[0];
			args[0] = temp;
		}
	}
}

void	ms_del_red(char **args, int pos)
{
	while (args[pos + 1])
	{
		args[pos - 1] = args [pos + 1];
		pos++;
	}
	args[pos - 1] = NULL;
	args[pos] = NULL;
}

void	ms_fork_init2(char **args, int *redir, int pip_end[2], int *fd_in)
{
	int	pip_rec;

	pip_rec = ft_pipe_check(args);
	if (pip_rec < 0)
		exit(-1);
	if (redir[0] > 0)
		dup2(redir[0], 0);
	else if (*fd_in > 0)
		dup2(*fd_in, 0);
	if (redir[1] > 0)
		close(pip_end[1]);
	if (redir[1] > 0)
		dup2(redir[1], 1);
	else if (pip_rec != 0)
		dup2(pip_end[1], 1);
	close(pip_end[0]);
}

int	ms_heredoc(int fd, char *s_eof)
{
	char	**line;

	if (!s_eof)
		return (-2);
	if (ms_heredoc_error(&line) == -2)
		return (-2);
	while (line && line[0] && ft_strcmp(line[0], s_eof) != 0)
	{
		write(fd, line[0], ft_strlen(line[0]));
		write(fd, "\n", 1);
		free(line[0]);
		line[0] = NULL;
		free(line);
		if (ms_heredoc_error(&line) == -2)
			return (-2);
	}
	if (line[0])
		free(line[0]);
	if (line)
		free(line);
	return (0);
}
