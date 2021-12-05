/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_register.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tglory <tglory@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 19:30:05 by tglory            #+#    #+#             */
/*   Updated: 2021/12/05 05:40:32 by tglory           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ms_command	*ms_cmd_register(char *name, char *description, 
				t_master *master, t_bool (*reg) (t_ms_command *))
{
	t_ms_command	*cmd;

	cmd = malloc(sizeof(*cmd));
	if (!cmd)
		return (NULL);
	cmd->name = name;
	cmd->description = description;
	cmd->master = master;
	cmd->analyze = NULL;
	cmd->execute = NULL;
	cmd->print = NULL;
	cmd->default_args = NULL;
	cmd->default_args_size = 0;
	if (!reg(cmd))
	{
		ft_println_red("Error > An error has occured while register cmd");
		return (NULL);
	}
	ft_lstadd_back(&(master->cmds), ft_lstnew(cmd));
	return (cmd);
}

void	ms_cmd_register_default_args(t_ms_command *cmd,
		char **default_args, int default_args_size)
{
	cmd->default_args = default_args;
	cmd->default_args_size = default_args_size;
}
