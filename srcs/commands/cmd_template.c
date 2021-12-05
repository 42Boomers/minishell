/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_template.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tglory <tglory@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 05:03:26 by tglory            #+#    #+#             */
/*   Updated: 2021/12/05 05:25:40 by tglory           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_bool	ms_template_analyze(t_ms_input *input)
{
	(void)input;
	return (TRUE);
}

static t_bool	ms_template_execute(t_ms_input *input)
{
	(void)input;
	return (TRUE);
}

static t_bool	ms_template_print(t_ms_input *input)
{
	(void)input;
	return (TRUE);
}

t_bool	ms_cmd_template_register(t_ms_command *cmd)
{
	cmd->analyze = &ms_template_analyze;
	cmd->execute = &ms_template_execute;
	cmd->print = &ms_template_print;
	return (TRUE);
}
