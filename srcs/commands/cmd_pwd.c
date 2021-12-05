/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tglory <tglory@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 21:11:17 by tglory            #+#    #+#             */
/*   Updated: 2021/12/05 08:23:01 by tglory           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ms_pwd(t_master *master)
{
	char	*env;

	env = ms_env_get(master, "PWD");
	if (!env)
		return (NULL);
	return (env);
}

static t_bool	ms_pwd_print(t_ms_input *input)
{
	printf("%s\n", ms_pwd(input->cmd->master));
	return (TRUE);
}

t_bool	ms_cmd_pwd_register(t_ms_command *cmd)
{
	cmd->print = &ms_pwd_print;
	return (TRUE);
}
