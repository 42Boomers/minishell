/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_launch.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tglory <tglory@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 05:00:00 by tglory            #+#    #+#             */
/*   Updated: 2021/12/20 21:34:59 by tglory           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ms_cmd_get_key(void *arg)
{
	t_ms_command	*cmd;

	cmd = arg;
	return (cmd->name);
}

t_ms_input	*ms_cmd_input(t_ms_command *cmd, char **args, int args_size)
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

static t_bool	ms_cmd_execute2(t_ms_input *input, t_bool cmd_result)
{
	if (input->cmd->print)
	{
		cmd_result = input->cmd->print(input);
		if (cmd_result != 1)
			return (FALSE);
	}
	return (TRUE);
}

t_bool	ms_cmd_execute(t_ms_input *input)
{
	t_bool	cmd_result;

	if (input->cmd->analyze)
	{
		cmd_result = input->cmd->analyze(input);
		if (cmd_result != 1)
			return (FALSE);
	}
	if (input->cmd->execute)
	{
		cmd_result = input->cmd->execute(input);
		if (cmd_result != 1)
			return (FALSE);
	}
	return (ms_cmd_execute2(input, cmd_result));
}

char	**ms_cmd_env_parse(t_master *master, char **args, int *args_size)
{
	int		i;
	int		j;
	char	**new_args;

	i = -1;
	j = 0;
	new_args = ms_mallocw(sizeof(char *) * (*args_size + 1), "Cannot malloc");
	if (!new_args)
		return (NULL);
	while (++i < *args_size)
	{
		new_args[j] = ms_env_parse(master, args[i]);
		// printf("ARG TRANS '%s' -> '%s'\n", args[i], new_args[j]);
		if (new_args[j])
			ms_garbage_master_add(master, new_args[j++], free); // TODO add to garbage of cmd
	}
	// ms_garbage_master_add(master, new_args, free);
	new_args[j] = 0;
	*args_size = j;
	return (new_args);
}

t_ms_command	*ms_cmd_launch(t_master *master, char *command,
		char **args, int args_size)
{
	args = ms_cmd_env_parse(master, args, &args_size);
	if (!args)
		return (NULL);
	ms_check_redir(&command, args);
	ms_fork(master, command, args, args_size);
	free(args);
	return (NULL);
}
