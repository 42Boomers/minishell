/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_launch_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrozniec <mrozniec@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 00:16:54 by mrozniec          #+#    #+#             */
/*   Updated: 2021/12/24 00:17:16 by mrozniec         ###   ########.fr       */
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
