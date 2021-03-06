/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_help.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tglory <tglory@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 21:11:17 by tglory            #+#    #+#             */
/*   Updated: 2021/12/16 16:49:55 by tglory           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ms_help_cmd(void *content)
{
	t_ms_command	*cmd;

	cmd = (t_ms_command *) content;
	printf(" | %s : %s\n", cmd->name, cmd->description);
}

static t_bool	ms_help_print(t_ms_input *input)
{
	input->cmd->master->cmd_ret = 0;
	ft_lstiter(input->cmd->master->cmds, ms_help_cmd);
	return (TRUE);
}

t_bool	ms_cmd_help_register(t_ms_command *cmd)
{
	cmd->print = &ms_help_print;
	return (TRUE);
}
