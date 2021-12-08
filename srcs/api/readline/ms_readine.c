/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_readine.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tglory <tglory@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 06:18:29 by tglory            #+#    #+#             */
/*   Updated: 2021/12/08 19:43:05 by tglory           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	ms_readline_two(t_master *master, char *input)
{
	char	**raw_args;
	char	**args;
	int		i;

	raw_args = ft_split(input, ' ');
	if (raw_args && raw_args[0])
	{
		ms_garbage_master_add(master, raw_args, free);
		i = 0;
		while (raw_args[i])
			ms_garbage_master_add(master, raw_args[i++], free);
		args = raw_args;
		ms_cmd_launch(master, raw_args[0], ++args, i - 1);
	}
	else
	{
		ms_cmd_launch(master, input, NULL, 0);
		if (raw_args)
			free(raw_args);
	}
	free(input);
	return (TRUE);
}

int	ms_readline_check(t_master *master, char **input)
{
	*input = readline("\e[36mminishell > \e[96m");
	if (!*input)
	{
		ft_putstr("\e[0m\n");
		return (1);
	}
	if (!**input)
	{
		free(*input);
		return (2);
	}
	ft_putstr("\e[0m");
	add_history(*input);
	mv_history_write(master, *input);
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
		if (ft_isequals_ignore("exit", input))
		{
			printf("\e[42mBye\e[0m\n");
			break ;
		}
		ms_readline_two(master, input);
	}
	if (input)
		free(input);
	return (TRUE);
}

t_bool	ms_readline(t_master *master)
{
	// ms_fork(ms_readline_single, master);
	ms_readline_one(master);
	return (TRUE);
}
