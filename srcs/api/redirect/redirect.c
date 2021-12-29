/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tglory <tglory@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 13:08:32 by tglory            #+#    #+#             */
/*   Updated: 2021/12/29 10:29:24 by mrozniec         ###   ########.fr       */
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
			return (i + 1);
		}
		if (ft_strcmp(args[i], "<<") == 0)
		{
			args[i] = NULL;
			return (-(i + 1));
		}
		if (ft_strcmp(args[i], "|") == 0 || ft_strcmp(args[i], ">") == 0 || \
		ft_strcmp(args[i], ">>") == 0)
			return (0);
	}
	return (0);
}

static int	ms_red_in(char **args, int *fd_red_in)
{
	int		pos;

	pos = ft_red_in_check(args);
	if (ft_check_bad(pos, args) == -1)
		return (-2);
	if (pos == 0)
		fd_red_in[0] = 0;
	while (pos != 0)
	{
		if (pos > 0)
			pos = ms_redir_open(fd_red_in, args, pos, 2);
		else if (pos < 0)
			pos = ms_redir_open(fd_red_in, args, pos, 3);
		if (pos != 0)
			return (pos);
		pos = ft_red_in_check(args);
		if (pos != 0)
		{
			if (close(*fd_red_in) == -1)
				return (-1);
			else if (ft_check_bad(pos, args) == -1)
				return (-2);
		}
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
			return (i + 1);
		}
		if (ft_strcmp(args[i], ">>") == 0)
		{
			args[i] = NULL;
			return (-(i + 1));
		}
		if (ft_strcmp(args[i], "|") == 0 || ft_strcmp(args[i], "<") == 0 || \
		ft_strcmp(args[i], "<<") == 0)
			return (0);
	}
	return (0);
}

static int	ms_red_out(char **args, int *fd_red_out)
{
	int	pos;

	pos = ft_red_out_check(args);
	if (ft_check_bad(pos, args) == -1)
		return (-2);
	if (pos == 0)
		fd_red_out[1] = 0;
	while (pos != 0)
	{
		if (pos > 0)
			pos = ms_redir_open(fd_red_out, args, pos, 0);
		else if (pos < 0)
			pos = ms_redir_open(fd_red_out, args, pos, 1);
		if (pos != 0)
			return (pos);
		pos = ft_red_out_check(args);
		if (pos != 0)
		{
			if (close(fd_red_out[1]) == -1)
				return (-1);
			else if (ft_check_bad(pos, args) == -1)
				return (-2);
		}
	}
	return (0);
}

int	ms_red_in_out(char **args, int *redir)
{
	int		ret;
	int		f_red;

	redir[0] = -5;
	redir[1] = -5;
	f_red = 1;
	while (f_red > 0)
	{
		if (f_red == (f_red | 4) && redir[0] > 0)
			close(redir[0]);
		if (f_red == (f_red | 2) && redir[1] > 0)
			close(redir[1]);
		ret = ms_red_in(args, redir);
		if (ret != 0)
		{
			if (redir[1] > 0)
				close(redir[1]);
			return (ft_redir_error(ret, args));
		}
		ret = ms_red_out(args, redir);
		if (ret != 0)
		{
			if (redir[0] > 0)
				close(redir[0]);
			return (ft_redir_error(ret, args));
		}
		f_red = ft_pres_red(args);
	}
	return (0);
}
