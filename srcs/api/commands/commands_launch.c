/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_launch.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblache <jblache@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 05:00:00 by jblache           #+#    #+#             */
/*   Updated: 2021/12/29 15:04:12 by jblache          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_bool	ms_cmd_execute2(t_ms_input *input, t_bool cmd_result)
{
	if (input->cmd->print)
	{
		cmd_result = input->cmd->print(input);
		if (cmd_result != TRUE)
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
		if (cmd_result != TRUE)
			return (FALSE);
	}
	if (input->cmd->execute)
	{
		cmd_result = input->cmd->execute(input);
		if (cmd_result != TRUE)
			return (FALSE);
	}
	return (ms_cmd_execute2(input, cmd_result));
}
/*
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
		new_args[i] = ft_strdup(args[i]);
	new_args[i] = 0;
	*args_size = i;
	return (new_args);
}

static void	*ms_cmd_launch_free(char *command, char **args)
{
	int	i;

	i = 0;
	while (args[i])
		free(args[i++]);
	free(args);
	if (command)
		free(command);
	return (NULL);
}
*/

t_ms_command	*ms_cmd_launch(t_master *master, char *command,
		char **args, int args_size)
{
	ms_check_redir(&command, args);
	ms_fork(master, command, args, args_size);
	return (NULL);
}
