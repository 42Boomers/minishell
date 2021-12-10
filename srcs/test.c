/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tglory <tglory@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 02:48:55 by tglory            #+#    #+#             */
/*   Updated: 2021/12/10 06:11:41 by tglory           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_test_cmd_execute(void *arg)
{
	t_ms_command	*cmd;

	cmd = arg;
	printf("\n%s\n\n", cmd->name);
	ms_cmd_launch(cmd->master, cmd->name, cmd->default_args, cmd->default_args_size);
}

t_bool	ms_test_cmd(t_master *master)
{
	ft_lstiter(master->cmds, ms_test_cmd_execute);
	return (TRUE);
}
