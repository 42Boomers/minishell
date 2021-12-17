/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrozniec <mrozniec@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 13:08:32 by mrozniec          #+#    #+#             */
/*   Updated: 2021/12/15 13:08:32 by mrozniec         ###   ########.fr       */
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

static void	ms_red_in(char **args, int *fd_red_in)
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
		}
		else if (pos < 0)
		{
			*fd_red_in = open(".ms_herefile", O_CREAT | O_WRONLY | O_TRUNC, \
			0641);
			ms_heredoc(*fd_red_in, args[-pos]);
			*fd_red_in = open(".ms_herefile", O_RDONLY);
			unlink(".ms_herefile");
			ms_del_red(args, -pos);
		}
		pos = ft_red_in_check(args);
		if (pos != 0)
			close(*fd_red_in);
	}
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

void	ms_red_in_out(char **args, int *redir)
{
	ms_red_in(args, redir);
	ms_red_out(args, redir);
}
