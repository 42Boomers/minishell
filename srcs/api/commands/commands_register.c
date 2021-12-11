/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_register.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tglory <tglory@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 19:30:05 by tglory            #+#    #+#             */
/*   Updated: 2021/12/11 01:49:38 by tglory           ###   ########lyon.fr   */
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
		ft_println_red("Error > An error has occured while registering cmd");
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
	ms_garbage_master_add(cmd->master, cmd->default_args, free);
}

/**
 * @brief Register here all cmds with ms_cmd_register
 * @param master 
 */
void	ms_cmd_register_all(t_master *master)
{
	ms_cmd_register("help", "This message",
		master, ms_cmd_help_register);
	ms_cmd_register("pwd", "Print current path",
		master, ms_cmd_pwd_register);
	ms_cmd_register("env", "Print all environment variables",
		master, ms_cmd_env_register); // syl : ICI
	ms_cmd_register("echo", "Print arguments",
		master, ms_cmd_echo_register);
	ms_cmd_register("cd", "Move to other directory",
		master, ms_cmd_cd_register);
	ms_cmd_register("unset", "Delete environment variable",
		master, ms_cmd_unset_register);
	ms_cmd_register("export", "Add environment variable",
		master, ms_cmd_export_register);
}
