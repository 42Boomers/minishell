/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_readine.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tglory <tglory@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 06:18:29 by tglory            #+#    #+#             */
/*   Updated: 2021/12/22 23:43:51 by tglory           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pipe_check(char **args)
{
	int	i;

	i = -1;
	while (args[++i])
	{
		if (ft_strcmp(args[i], "|") == 0)
		{
			args[i] = NULL;
			if (!args[i + 1])
				return (0);
			if (ft_strcmp(args[i + 1], "|") == 0)
				return (-(i + 1));
			return (i + 1);
		}
	}
	return (0);
}

t_bool	ms_readline_two(t_master *master, char *input)
{
	char	**raw_args;
	int		i;

	raw_args = ft_split_ultimate(input, ' ');
	if (raw_args && raw_args[0])
	{
		i = 0;
		while (raw_args[i])
			ms_garbage_master_add(master, raw_args[i++], free);
		ms_garbage_master_add(master, raw_args, free);
		ms_cmd_launch(master, raw_args[0], raw_args + 1, i - 1);
		// raw_args++;
	}
	else
	{
		// tglory : je me souviens pourquoi j'ai fais sa, ça devrais jamais arriver.
		printf("DEBUG : this happend. Don't delete me pls\n");
		ms_cmd_launch(master, input, NULL, 0);
		if (raw_args)
			free(raw_args);
	}
	free(input);
	return (TRUE);
}

int	ms_readline_check(t_master *master, char **input)
{
	char	*prefix;

	prefix = ms_prefix_get(master);
	*input = readline(prefix);
	free(prefix);
	if (!*input)
	{
		ft_putstr("\e[0m\n");
		return (1);
	}
	if (!**input || ft_isblank(*input))
	{
		free(*input);
		return (2);
	}
	ft_putstr("\e[0m");
	add_history(*input);
	ms_history_write(master, *input);
	return (0);
}

t_bool	ms_readline_one(t_master *master)
{
	char	*input;
	int		i;

	input = NULL;
	while (TRUE)
	{
		i = ms_readline_check(master, &input);
		if (i == 1)
			break ;
		else if (i == 2)
			continue ;
		if (!ms_readline_two(master, input))
			break ;
	}
	if (input)
		free(input);
	return (TRUE);
}

t_bool	ms_readline(t_master *master)
{
	ms_readline_one(master);
	return (TRUE);
}
