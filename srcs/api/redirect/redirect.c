//
// Created by Maximilien Rozniecki on 12/14/21.
//

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
	int pos;

	pos = ft_red_in_check(args);
	if (pos > 0)
	{
		*fd_red_in = open(args[pos], O_RDONLY);
		while (args[pos + 1])
		{
			args[pos - 1] = args [pos + 1];
			pos++;
		}
		args[pos - 1] = args[pos];
		args[pos] = NULL;
	}
	else if (pos < 0)
	{
		pos = -pos;
		while (args[pos + 1])
		{
			args[pos - 1] = args [pos + 1];
			pos++;
		}
		args[pos - 1] = args[pos];
		args[pos] = NULL;
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
	int pos;

	pos = ft_red_out_check(args);
	if (pos > 0)
	{
		fd_red_out[1] = open(args[pos], O_CREAT | O_RDWR | O_TRUNC, 0644);
		while (args[pos + 1])
		{
			args[pos - 1] = args [pos + 1];
			pos++;
		}
		args[pos - 1] = args[pos];
		args[pos] = NULL;
	}
	else if (pos < 0)
	{
		pos = -pos;
		fd_red_out[1] = open(args[pos], O_CREAT | O_RDWR | O_APPEND, 0644);
		while (args[pos + 1])
		{
			args[pos - 1] = args [pos + 1];
			pos++;
		}
		args[pos - 1] = args[pos];
		args[pos] = NULL;
	}
}

void	ms_red_in_out(char **args, int *redir)
{
	ms_red_in(args, redir);
	ms_red_out(args, redir);
}