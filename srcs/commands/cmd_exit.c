/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tglory <tglory@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 05:03:26 by tglory            #+#    #+#             */
/*   Updated: 2021/12/22 23:52:12 by tglory           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
// @jblache
// exit should check if it's exit is num and how appropriate message
// and if is num exit the program with this num;
static void	ms_exit(t_ms_input *input, int status_code)
{
	ms_free_master(input->cmd->master);
	exit(status_code);
}

// static t_bool	ms_exit_execute(t_ms_input *input)
// {
// 	ms_exit(input, input->cmd->master->cmd_ret);
// 	return (TRUE);
// }

static t_bool	ms_exit_execute(t_ms_input *input)
{
	int	status_code;
	int	i;

	status_code = input->cmd->master->cmd_ret;
	printf("exit\n");
	if (input->args_size == 0)
		ms_exit(input, status_code);
	i = -1;
	while (input->args[0][++i])
	{
		if (!ft_isdigit(input->args[0][i]))
		{
			fprintf(stderr, "minishell: exit: %s: numeric argument required\n",
				input->args[0]);
			ms_exit(input, 2);
		}
	}
	if (input->args_size > 1)
	{
		fprintf(stderr, "minishell: exit: too many arguments\n");
		return (FALSE);
	}
	status_code = ft_atoi(input->args[0]);
	ms_exit(input, status_code);
	return (TRUE);
}

t_bool	ms_cmd_exit_register(t_ms_command *cmd)
{
	cmd->master->cmd_ret = 0;
	cmd->execute = &ms_exit_execute;
	return (TRUE);
}
