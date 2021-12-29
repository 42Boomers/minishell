/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrozniec <mrozniec@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 21:11:17 by mrozniec          #+#    #+#             */
/*   Updated: 2021/12/28 15:15:14 by mrozniec         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_bool	ms_pwd_print(t_ms_input *input)
{
	char	*pwd;

	pwd = ms_pwd_buff(input->cmd->master->name, "pwd", 128);
	if (!pwd)
		return (FALSE);
	ft_putstr(pwd);
	free(pwd);
	ft_putchar('\n');
	return (TRUE);
}

t_bool	ms_cmd_pwd_register(t_ms_command *cmd)
{
	cmd->master->cmd_ret = 0;
	cmd->print = &ms_pwd_print;
	return (TRUE);
}
