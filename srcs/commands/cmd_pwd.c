/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tglory <tglory@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 21:11:17 by tglory            #+#    #+#             */
/*   Updated: 2021/12/21 21:10:50 by tglory           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_bool	ms_pwd_print(t_ms_input *input)
{
	char	*pwd;

	pwd = ms_pwd(input->cmd->master);
	if (pwd)
		ft_putstr(pwd);
	ft_putchar('\n');
	return (pwd != NULL);
}

t_bool	ms_cmd_pwd_register(t_ms_command *cmd)
{
	cmd->master->cmd_ret = 0;
	cmd->print = &ms_pwd_print;
	return (TRUE);
}
