/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tglory <tglory@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 05:03:26 by tglory            #+#    #+#             */
/*   Updated: 2021/12/16 23:28:21 by tglory           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ms_change_pwd(int buff_size)
{
	char	*buff;

	buff = malloc(sizeof(char) * buff_size);
	if (!buff)
		return (NULL);
	getcwd(buff, buff_size);
	if (errno == EACCES || errno == EFAULT
		|| errno == EINVAL || errno == ENOENT)
		return (NULL);
	else if (errno == ERANGE)
	{
		free(buff);
		return (ms_change_pwd(buff_size * 2));
	}
	return (buff);
}

static t_bool	ms_cd_execute(t_ms_input *input)
{
	char	*new_pwd;

	if (input->args_size == 0)
		return (FALSE);
	if (ms_file_is_dir(input->args[0]) != 1)
	{
		printf("cd: no such directory: %s\n", input->args[0]);
		return (FALSE);
	}
	chdir(input->args[0]);
	new_pwd = ms_change_pwd(128);
	if (!new_pwd)
	{
		printf("cd: unable to change current dir to %s\n", input->args[0]);
		return (FALSE);
	}
	ms_pwd_set(input->cmd->master, new_pwd);
	free(new_pwd);
	return (TRUE);
}

t_bool	ms_cmd_cd_register(t_ms_command *cmd)
{
	cmd->execute = &ms_cd_execute;
	return (TRUE);
}
