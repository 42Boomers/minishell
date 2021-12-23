/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tglory <tglory@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 05:03:26 by tglory            #+#    #+#             */
/*   Updated: 2021/12/24 00:42:19 by tglory           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	n_check(char *first_arg)
{
	int	i;

	if (*first_arg == '-')
	{
		i = 0;
		while (first_arg[++i])
			if (first_arg[i] != 'n')
				return (FALSE);
		return (i > 1);
	}
	return (FALSE);
}

static t_bool	ms_echo_print(t_ms_input *input)
{
	int		arg_n;

	input->cmd->master->cmd_ret = 0;
	arg_n = 0;
	while (*input->args && n_check(*input->args))
	{
		arg_n = 1;
		input->args++;
	}
	while (*input->args)
	{
		ft_putstr(*input->args);
		if (*(input->args + 1))
			ft_putchar(' ');
		input->args++;
	}
	if (!arg_n)
		ft_putchar('\n');
	return (TRUE);
}

t_bool	ms_cmd_echo_register(t_ms_command *cmd)
{
	char	**args;
	int		i;

	cmd->print = &ms_echo_print;
	i = 0;
	args = malloc(sizeof(char *) * 6);
	args[i++] = "Hello";
	args[i++] = "World\n";
	args[i++] = "\"Ceci est un test\"\n";
	args[i++] = "$NAME\n";
	args[i++] = "$PATH";
	args[i++] = "\n$PWD_$NAME";
	ms_cmd_register_default_args(cmd, args, i);
	return (TRUE);
}
