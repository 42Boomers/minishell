/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tglory <tglory@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 05:03:26 by tglory            #+#    #+#             */
/*   Updated: 2021/12/21 18:03:30 by tglory           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ms_exit(t_ms_input *input, int status_code)
{
	ms_free_master(input->cmd->master);
	exit(status_code);
}

static t_bool	ms_exit_execute(t_ms_input *input)
{
	int	status_code;
	int	i;

	printf("exit\n");
	if (input->args_size == 0)
		ms_exit(input, input->cmd->master->cmd_ret);
	if (input->args_size > 1)
	{
		fprintf(stderr, "minishell: exit: too many arguments\n");
		return (FALSE);
	}
	// if (!ft_str_isall(input->args[0], ft_isdigit))
	// {
	// 	fprintf(stderr, "minishell: exit: %s: numeric argument required\n", input->args[0]);
	// 	return (FALSE);
	// }
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
