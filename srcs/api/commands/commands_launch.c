/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_launch.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tglory <tglory@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 05:00:00 by tglory            #+#    #+#             */
/*   Updated: 2021/12/05 05:06:45 by tglory           ###   ########lyon.fr   */
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
		char **args, int args_size)
{
	t_ms_command	*cmd;
	t_ms_input		*input;

	ft_lstadd_back(&(master->history), ft_lstnew(ft_strdup(command)));
	cmd = ft_lstget(master->cmds, command, ms_cmd_get_key);
	if (!cmd)
	{
		printf("\e[31mminishell: command not found: %s.\n\e[0m", command);
		return (NULL);
	}
	input = ms_cmd_input(cmd, args, args_size);
	ms_cmd_execute(input);
	ms_garbage_free(&input->garbage);
	free(input);
	return (cmd);
}
