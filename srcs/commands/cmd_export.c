/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tglory <tglory@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 05:03:26 by tglory            #+#    #+#             */
/*   Updated: 2021/12/16 16:28:49 by tglory           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_bool	ms_export_analyze(t_ms_input *input)
{
	(void)input;
	return (TRUE);
}

static t_bool	ms_export_execute(t_ms_input *input)
{
	int	i;

	input->cmd->master->cmd_ret = 0;
	i = 0;
	while (input->args_size > i)
	{
		if (!ms_env_add_raw(input->cmd->master, input->args[i]))
			printf("Can't add %s\n", input->args[i]);
		i++;
	}
	return (TRUE);
}

static t_bool	ms_export_print(t_ms_input *input)
{
	(void)input;
	return (TRUE);
}

t_bool	ms_cmd_export_register(t_ms_command *cmd)
{
	cmd->analyze = &ms_export_analyze;
	cmd->execute = &ms_export_execute;
	cmd->print = &ms_export_print;
	return (TRUE);
}
