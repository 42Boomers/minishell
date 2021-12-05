/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tglory <tglory@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 21:11:17 by tglory            #+#    #+#             */
/*   Updated: 2021/12/05 02:45:50 by tglory           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	ms_pwd_analyze(t_ms_input *input)
{
	(void)input;
	return (TRUE);
}

t_bool	ms_pwd_execute(t_ms_input *input)
{
	(void)input;
	return (TRUE);
}

t_bool	ms_pwd_print(t_ms_input *input)
{
	printf("%s\n", ms_pwd(input->cmd->master));
	return (TRUE);
}

t_bool	ms_cmd_pwd_register(t_ms_command *cmd)
{
	cmd->analyze = &ms_pwd_analyze;
	cmd->execute = &ms_pwd_execute;
	cmd->print = &ms_pwd_print;
	return (TRUE);
}
