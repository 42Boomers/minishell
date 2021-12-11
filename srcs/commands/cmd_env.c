/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tglory <tglory@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 21:11:17 by tglory            #+#    #+#             */
/*   Updated: 2021/12/11 01:29:58 by tglory           ###   ########lyon.fr   */
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
	ms_write(ms_env_format(input->cmd->master), ft_lstsize(input->cmd->master->envs));
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
