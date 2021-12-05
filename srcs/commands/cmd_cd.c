/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tglory <tglory@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 05:03:26 by tglory            #+#    #+#             */
/*   Updated: 2021/12/05 14:32:17 by tglory           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_bool	ms_cd_analyze(t_ms_input *input)
{
	(void)input;
	return (TRUE);
}

static t_bool	ms_cd_execute(t_ms_input *input)
{
	(void)input;
	return (TRUE);
}

static t_bool	ms_cd_print(t_ms_input *input)
{
	(void)input;
	return (TRUE);
}

t_bool	ms_cmd_cd_register(t_ms_command *cmd)
{
	cmd->analyze = &ms_cd_analyze;
	cmd->execute = &ms_cd_execute;
	cmd->print = &ms_cd_print;
	return (TRUE);
}
