/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrozniec <mrozniec@student.42lyon.fr>      +#+  +:+       +#+        */
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
			if (*fd_red_in == -1)
				return (pos);
			ms_del_red(args, pos);
		}
		else if (pos < 0)
		{
			*fd_red_in = open(".ms_heredoc", O_CREAT | O_WRONLY | O_TRUNC, \
			0641);
			if (*fd_red_in == -1)
				return (-1);
			ms_heredoc(*fd_red_in, args[-pos]);
			*fd_red_in = open(".ms_heredoc", O_RDONLY);
			if (*fd_red_in == -1)
				return (-1);
			unlink(".ms_heredoc");
			ms_del_red(args, -pos);
		}
		pos = ft_red_in_check(args);
		if (pos != 0)
			if (close(*fd_red_in) == -1)
				return (-1);
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

static int	ms_red_out(char **args, int *fd_red_out)
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
			if (fd_red_out[1] == -1)
				return (pos);
			ms_del_red(args, pos);
		}
		else if (pos < 0)
		{
			fd_red_out[1] = open(args[-pos], O_CREAT | O_WRONLY | O_APPEND, \
			0641);
			if (fd_red_out[1] == -1)
				return (-pos);
			ms_del_red(args, -pos);
		}
		pos = ft_red_out_check(args);
		if (pos != 0)
			if (close(fd_red_out[1]) == -1)
				return (-1);
	}
	return (0);
}

int	ms_red_in_out(char **args, int *redir)
{
	int		ret;
	char	*strer;

	ret = ms_red_in(args, redir);
	if (ret != 0)
	{
		if (ret > 0)
		{
			strer = ft_strjoin("minishell: ", args[ret]);
			perror(strer);
			free(strer);
		}
		else if (ret < 0)
			perror("minishell");
		return (-1);
	}
	ret = ms_red_out(args, redir);
	if (ret != 0)
	{
		if (ret > 0)
		{
			strer = ft_strjoin("minishell: ", args[ret]);
			perror(strer);
			free(strer);
		}
		else if (ret < 0)
			perror("minishell");
		return (-1);
	}
	return (0);
}
