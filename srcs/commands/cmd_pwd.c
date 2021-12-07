/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sylducam <sylducam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 21:11:17 by tglory            #+#    #+#             */
/*   Updated: 2021/12/07 19:12:00 by sylducam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_bool	ms_pwd_print(t_ms_input *input)
{
	printf("%s\n", ms_pwd(input->cmd->master)); // syl : what's the difference with the original master ?
	return (TRUE);
}

t_bool	ms_cmd_pwd_register(t_ms_command *cmd)
{
	cmd->print = &ms_pwd_print;
	return (TRUE);
}
