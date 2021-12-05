/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tglory <tglory@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 05:03:26 by tglory            #+#    #+#             */
/*   Updated: 2021/12/05 14:32:00 by tglory           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_bool	ms_unset_analyze(t_ms_input *input)
{
	(void)input;
	return (TRUE);
}

static t_bool	ms_unset_execute(t_ms_input *input)
{
	(void)input;
	return (TRUE);
}

static t_bool	ms_unset_print(t_ms_input *input)
{
	(void)input;
	return (TRUE);
}

t_bool	ms_cmd_unset_register(t_ms_command *cmd)
{
	cmd->analyze = &ms_unset_analyze;
	cmd->execute = &ms_unset_execute;
	cmd->print = &ms_unset_print;
	return (TRUE);
}
