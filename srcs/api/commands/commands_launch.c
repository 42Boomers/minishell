/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_launch.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tglory <tglory@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 05:00:00 by tglory            #+#    #+#             */
/*   Updated: 2021/12/10 03:12:27 by tglory           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ms_cmd_get_key(void *arg)
{
	t_ms_command	*cmd;

	cmd = arg;
	return (cmd->name);
}

static t_ms_input	*ms_cmd_input(t_ms_command *cmd, char **args, int args_size)
{
	t_ms_input	*input;

	input = malloc(sizeof(*input));
	if (!input)
	{
		ft_println_red("Error > Unable to malloc t_ms_input");
		return (NULL);
	}
	input->args = args;
	input->args_size = args_size;
	input->cmd = cmd;
	input->garbage = NULL;
	return (input);
}

static t_bool	ms_cmd_execute(t_ms_input *input)
{
	t_bool	cmd_result;

	if (input->cmd->analyze)
	{
		cmd_result = input->cmd->analyze(input);
		if (cmd_result == -1)
			ft_println_red("Error > An error has occured while analyze cmd");
		else if (cmd_result != 1)
			return (FALSE);
	}
	if (input->cmd->execute)
	{
		cmd_result = input->cmd->execute(input);
		if (cmd_result == -1)
			ft_println_red("Error > An error has occured while execute cmd");
		else if (cmd_result != 1)
			return (FALSE);
	}
	if (input->cmd->print)
	{
		cmd_result = input->cmd->print(input);
		if (cmd_result == -1)
			ft_println_red("Error > An error has occured while print cmd");
		else if (cmd_result != 1)
			return (FALSE);
	}
	return (TRUE);
}

t_ms_command	*ms_cmd_launch(t_master *master, char *command,
		char **args, int args_size)
{
	t_ms_command	*cmd;
	t_ms_input		*input;

	cmd = ft_lstget(master->cmds, command, ms_cmd_get_key);
	if (!cmd)
	{
		if (!ms_cmd_os(master, command, args))
		{
			mv_set_status(master, FALSE);
			printf("\e[31mminishell: %s: command not found\n\e[0m", command);
		}
		return (NULL);
	}
	input = ms_cmd_input(cmd, args, args_size);
	mv_set_status(master, ms_cmd_execute(input));
	ms_garbage_free(&input->garbage);
	free(input);
	return (cmd);
}
