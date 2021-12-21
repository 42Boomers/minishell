/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tglory <tglory@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 13:08:32 by mrozniec          #+#    #+#             */
/*   Updated: 2021/12/21 02:20:25 by tglory           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_red_in_check(char **args)
{
	int	i;

	i = -1;
	while (args[++i])
	{
		if (ft_strcmp(args[i], "<") == 0)
		{
			args[i] = NULL;
			if (!args[i + 1])
				return (0);
			return (i + 1);
		}
		if (ft_strcmp(args[i], "<<") == 0)
		{
			args[i] = NULL;
			if (!args[i + 1])
				return (0);
			return (-(i + 1));
		}
		if (ft_strcmp(args[i], "|") == 0)
			return (0);
	}
	return (0);
}

static int	ms_red_in(char **args, int *fd_red_in)
{
	int		pos;

	pos = ft_red_in_check(args);
	if (pos == 0)
		fd_red_in[0] = 0;
	while (pos != 0)
	{
		if (pos > 0)
		{
			*fd_red_in = open(args[pos], O_RDONLY);
			ms_del_red(args, pos);
			if (*fd_red_in == -1)
				return(pos);
		}
		else if (pos < 0)
		{
			*fd_red_in = open(".ms_heredoc", O_CREAT | O_WRONLY | O_TRUNC, \
			0641);
			ms_heredoc(*fd_red_in, args[-pos]);
			*fd_red_in = open(".ms_heredoc", O_RDONLY);
			unlink(".ms_heredoc");
			ms_del_red(args, -pos);
		}
		pos = ft_red_in_check(args);
		if (pos != 0)
			close(*fd_red_in);
	}
	return (0);
}

static int	ft_red_out_check(char **args)
{
	int	i;

	i = -1;
	while (args[++i])
	{
		if (ft_strcmp(args[i], ">") == 0)
		{
			args[i] = NULL;
			if (!args[i + 1])
				return (0);
			return (i + 1);
		}
		if (ft_strcmp(args[i], ">>") == 0)
		{
			args[i] = NULL;
			if (!args[i + 1])
				return (0);
			return (-(i + 1));
		}
		if (ft_strcmp(args[i], "|") == 0)
			return (0);
	}
	return (0);
}

static void	ms_red_out(char **args, int *fd_red_out)
{
	int	pos;

	pos = ft_red_out_check(args);
	if (pos == 0)
		fd_red_out[1] = 0;
	while (pos != 0)
	{
		if (pos > 0)
		{
			fd_red_out[1] = open(args[pos], O_CREAT | O_WRONLY | O_TRUNC, 0641);
			ms_del_red(args, pos);
		}
		else if (pos < 0)
		{
			pos = -pos;
			fd_red_out[1] = open(args[pos], O_CREAT | O_WRONLY | O_APPEND, \
			0641);
			ms_del_red(args, pos);
		}
		pos = ft_red_out_check(args);
		if (pos != 0)
			close(fd_red_out[1]);
	}
}

int	ms_red_in_out(char **args, int *redir)
{
	int	ret;

	ret = ms_red_in(args, redir);
	if (ret != 0)
	{
		fprintf(stderr, "\e[31mminishell: %s: No such file or directory\n\e[0m"\
				, args[ret]);
		return (-1);
	}
	ms_red_out(args, redir);
	return (0);
}
