/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tglory <tglory@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 21:11:17 by tglory            #+#    #+#             */
/*   Updated: 2021/12/05 08:10:37 by tglory           ###   ########lyon.fr   */
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
	// char			***envs;
	// int				i;

	// envs = input->cmd->master->envs;
	// i = 0;
	// while (i < input->cmd->master->envs_size)
	// {
	// 	printf("%s=%s\n", envs[i][0], envs[i][1]);
	// 	i++;
	// }
	ms_write(ms_env_format(input->cmd->master), input->cmd->master->envs_size);
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
