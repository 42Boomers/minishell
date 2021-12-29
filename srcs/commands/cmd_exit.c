/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblache <jblache@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 05:03:26 by jblache           #+#    #+#             */
/*   Updated: 2021/12/29 16:00:36 by jblache          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ms_exit(t_ms_input *input, int status_code)
{
	ms_free_master(input->cmd->master);
	exit(status_code);
}

static void	ms_exit_error(t_ms_input *input, int i)
{
	if (input->args[0][i] == '+' && input->args[0][i + 1] != '-')
		i++;
	if (ft_strcmp(ft_itoa(ft_atoi(&input->args[0][i])), &input->args[0][i]))
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(input->args[0], 2);
		ft_putendl_fd(": numeric argument required", 2);
		ms_exit(input, 255);
	}
}

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
		ms_exit_error(input, i);
	if (input->args_size > 1)
	{
		ft_putstr_fd(input->cmd->master->name, 2);
		ft_putendl_fd(": exit: too many arguments", 2);
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
