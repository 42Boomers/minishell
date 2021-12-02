/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_register.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tglory <tglory@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 19:30:05 by tglory            #+#    #+#             */
/*   Updated: 2021/12/02 23:34:43 by tglory           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ms_cmd_get_key(void *arg)
{
	t_ms_command	*cmd;

	cmd = arg;
	return (cmd->name);
}

t_ms_command	*ms_cmd_register(char *name, t_master *master, t_bool (*reg) (t_ms_command *))
{
	t_ms_command	*cmd;

	cmd = ms_malloc(master, sizeof(t_ms_command));
	if (!cmd)
	{
		ft_println_red("Error > An error has occured while malloc cmd");
		return (NULL);
	}
	cmd->name = name;
	cmd->master = master;
	if (!reg(cmd))
	{
		ft_println_red("Error > An error has occured while register cmd");
		return (NULL);
	}
	ft_lstadd_back(&(master->cmds), ft_lstnew(cmd));
	return (cmd);
}

t_ms_input	*ms_cmd_input(t_ms_command *cmd, char **args, int length)
{
	t_ms_input	*input;

	input = ms_malloc(cmd->master, sizeof(t_ms_input));
	if (!input)
		return (NULL);
	input->args = args;
	input->length = length;
	input->cmd = cmd;
	return (input);
}

t_ms_command	*ms_cmd_launch(t_master *master, char *command, char **args, int length)
{
	t_ms_command	*cmd;
	t_ms_input		*input;

	cmd = ft_lstget(master->cmds, command, ms_cmd_get_key);
	if (!cmd)
	{
		ft_println_orange("Unknown command");
		return (NULL);
	}
	input = ms_cmd_input(cmd, args, length);
	if (!cmd->analyze(input))
	{
		ft_println_red("Error > An error has occured while analyze cmd");
		return (NULL);
	}
	if (!cmd->execute(input))
	{
		ft_println_red("Error > An error has occured while execute cmd");
		return (NULL);
	}
	if (!cmd->print(input))
	{
		ft_println_red("Error > An error has occured while print cmd");
		return (NULL);
	}
	return (cmd);
}
