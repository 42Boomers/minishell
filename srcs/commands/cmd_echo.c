/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tglory <tglory@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 05:03:26 by tglory            #+#    #+#             */
/*   Updated: 2021/12/05 05:47:05 by tglory           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static t_bool	ms_echo_analyze(t_ms_input *input)
// {
// 	(void)input;
// 	return (TRUE);
// }

// static t_bool	ms_echo_execute(t_ms_input *input)
// {
// 	(void)input;
// 	return (TRUE);
// }

static t_bool	ms_echo_print(t_ms_input *input)
{
	int		i;
	int		arg_n;

	i = -1;
	arg_n = 0;
	while (++i < input->args_size)
	{
		if (ft_isequals_ignore("-n", input->args[i]))
		{
			arg_n = 1;
			continue ;
		}
		ft_putstr(input->args[i]);
		if (i + 1 < input->args_size)
			ft_putchar(' ');
	}
	if (!arg_n)
		ft_putchar('\n');
	return (TRUE);
}

t_bool	ms_cmd_echo_register(t_ms_command *cmd)
{
	// cmd->analyze = &ms_echo_analyze;
	// cmd->execute = &ms_echo_execute;
	cmd->print = &ms_echo_print;
	return (TRUE);
}
