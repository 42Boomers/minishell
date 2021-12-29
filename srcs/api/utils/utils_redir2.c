/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_redir2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tglory <tglory@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 16:53:00 by tglory            #+#    #+#             */
/*   Updated: 2021/12/29 10:52:16 by mrozniec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_heredoc(int *fd, char **args, int pos)
{
	*fd = open(".ms_heredoc", O_CREAT | O_WRONLY | O_TRUNC, 0641);
	if (*fd == -1)
		return (-1);
	if (ms_heredoc(*fd, args[-pos]) == -2)
	{
		close(*fd);
		return (-2);
	}
	close(*fd);
	*fd = open(".ms_heredoc", O_RDONLY);
	if (*fd == -1)
		return (-1);
	unlink(".ms_heredoc");
	ms_del_red(args, -pos);
	return (0);
}

int	ms_redir_open(int *fd, char **args, int pos, int option)
{
	if (option == 0)
	{
		fd[1] = open(args[pos], O_CREAT | O_WRONLY | O_TRUNC, 0641);
		if (fd[1] == -1)
			return (pos);
		ms_del_red(args, pos);
	}
	else if (option == 1)
	{
		fd[1] = open(args[-pos], O_CREAT | O_WRONLY | O_APPEND, \
			0641);
		if (fd[1] == -1)
			return (-pos);
		ms_del_red(args, -pos);
	}
	else if (option == 2)
	{
		*fd = open(args[pos], O_RDONLY);
		if (*fd == -1)
			return (pos);
		ms_del_red(args, pos);
	}
	else if (option == 3)
		return (ft_heredoc(fd, args, pos));
	return (0);
}

int	ms_bad_redir_error(char **args, int pos)
{
	char	*ret;

	ret = \
		ft_strjoin_plus("minishell: syntax error near unexpected token `", \
		args[pos], "\'\n");
	ft_putstr_fd(ret, 2);
	free(ret);
	return (-1);
}
