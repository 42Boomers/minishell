/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_register.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tglory <tglory@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 19:30:05 by tglory            #+#    #+#             */
/*   Updated: 2021/12/02 19:49:57 by tglory           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ms_cmd_get_key(void *arg)
{
	t_ms_command	*cmd;

	cmd = arg;
	return (cmd->name);
}

t_ms_command	*ms_cmd_launch(t_master *master, char *command)
{
	t_ms_command	*cmd;

	cmd = ft_lstget(master->cmds, command, ms_cmd_get_key);
	if (!cmd)
		return (NULL);
	return (cmd);
}
