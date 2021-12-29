/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblache <jblache@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 21:11:17 by tglory            #+#    #+#             */
/*   Updated: 2021/12/29 12:06:36 by jblache          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Print command ENV
 * Print all the environment variable.
 * @param input
 * @return t_bool
 */
static t_bool	ms_env_print(t_ms_input *input)
{
	int	i;

	i = 0;
	while (input->args[i])
	{
		if (ft_strcmp(input->args[i], "env"))
		{
			ft_putstr_fd("env: ", 2);
			ft_putstr_fd(input->args[i], 2);
			ft_putstr_fd(": No such file or directory\n", 2);
			exit(127);
		}
		i++;
	}
	ms_write(ms_env_format(input->cmd->master),
		ft_lstsize(input->cmd->master->envs));
	return (TRUE);
}

/**
 * @brief Register theses functions has command
 * @param cmd
 * @return t_bool
 */
t_bool	ms_cmd_env_register(t_ms_command *cmd)
{
	cmd->print = &ms_env_print;
	return (TRUE);
}
