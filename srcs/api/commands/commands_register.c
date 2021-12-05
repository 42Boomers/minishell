/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_register.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tglory <tglory@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 19:30:05 by tglory            #+#    #+#             */
/*   Updated: 2021/12/05 04:03:06 by tglory           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ms_cmd_get_key(void *arg)
{
	t_ms_command	*cmd;

	cmd = arg;
	return (cmd->name);
}

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
	if (!reg(cmd))
	{
		ft_println_red("Error > An error has occured while register cmd");
		return (NULL);
	}
	ft_lstadd_back(&(master->cmds), ft_lstnew(cmd));
	return (cmd);
}

static t_ms_input	*ms_cmd_input(t_ms_command *cmd, char **args, int length)
{
	t_ms_input	*input;

	input = malloc(sizeof(*input));
	if (!input)
	{
		ft_println_red("Error > Unable to malloc t_ms_input");
		return (NULL);
	}
	input->args = args;
	input->length = length;
	input->cmd = cmd;
	input->garbage = NULL;
	return (input);
}

static t_bool	ms_cmd_execute(t_ms_input *input)
{
	t_ms_command	*cmd;

	cmd = input->cmd;
	if (cmd->analyze && !cmd->analyze(input))
	{
		ft_println_red("Error > An error has occured while analyze cmd");
		return (FALSE);
	}
	if (cmd->execute && !cmd->execute(input))
	{
		ft_println_red("Error > An error has occured while execute cmd");
		return (FALSE);
	}
	if (cmd->print && !cmd->print(input))
	{
		ft_println_red("Error > An error has occured while print cmd");
		return (FALSE);
	}
	return (TRUE);
}

t_ms_command	*ms_cmd_launch(t_master *master, char *command,
		char **args, int length)
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
	ms_cmd_execute(input);
	ms_garbage_free(&input->garbage);
	free(input);
	return (cmd);
}
