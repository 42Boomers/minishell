/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblache <jblache@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 21:11:17 by tglory            #+#    #+#             */
/*   Updated: 2021/12/28 14:28:31 by jblache          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_bool	ms_pwd_print(t_ms_input *input)
{
	char	pwd[1024];

	(void)input;
	getcwd(pwd, 1024);
	ft_putstr(pwd);
	ft_putchar('\n');
	return (TRUE);
}

t_bool	ms_cmd_pwd_register(t_ms_command *cmd)
{
	cmd->master->cmd_ret = 0;
	cmd->print = &ms_pwd_print;
	return (TRUE);
}
