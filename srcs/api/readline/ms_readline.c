/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_readline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tglory <tglory@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 06:18:29 by tglory            #+#    #+#             */
/*   Updated: 2021/12/28 16:10:13 by tglory           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	ms_readline_two(t_master *master, char *input)
{
	char	**raw_args;
	int		i;

	raw_args = ft_split_ultimate(master, input, ' ');
	if (raw_args && raw_args[0])
	{
		i = 0;
		/*while (raw_args[i])
			ms_garbage_master_add(master, raw_args[i++], free);
		ms_garbage_master_add(master, raw_args, free);*/
		ms_cmd_launch(master, raw_args[0], raw_args + 1, i - 1);
		while (raw_args[i])
			free(raw_args[i++]);
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
		ft_putstr("\e[0mexit\n");
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
