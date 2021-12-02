/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tglory <tglory@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 21:11:17 by tglory            #+#    #+#             */
/*   Updated: 2021/12/02 23:42:21 by tglory           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	ms_env_analyze(t_ms_input *input)
{
	(void)input;
	return (TRUE);
}

t_bool	ms_env_execute(t_ms_input *input)
{
	(void)input;
	return (TRUE);
}

t_bool	ms_env_print(t_ms_input *input)
{
	ft_env_print_all(input->cmd->master->envs);
	return (TRUE);
}

t_bool	ms_cmd_env_register(t_ms_command *cmd)
{
	cmd->analyze = &ms_env_analyze;
	cmd->execute = &ms_env_execute;
	cmd->print = &ms_env_print;
	return (TRUE);
}
