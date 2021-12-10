/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tglory <tglory@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 05:03:26 by tglory            #+#    #+#             */
/*   Updated: 2021/12/10 05:26:12 by tglory           ###   ########lyon.fr   */
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
	char	*new_pwd;

	if (input->args_size == 0)
	{
		printf("cd: cd relative path in dev\n");
		return (FALSE);
	}
	new_pwd = input->args[0];
	if (ms_file_is_dir(new_pwd) != 1)
	{
		printf("cd: no such directory: %s\n", new_pwd);
		return (FALSE);
	}
	chdir(new_pwd);
	ms_pwd_set(input->cmd->master, new_pwd);
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
