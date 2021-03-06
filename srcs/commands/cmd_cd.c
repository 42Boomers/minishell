/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tglory <tglory@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 05:03:26 by tglory            #+#    #+#             */
/*   Updated: 2021/12/28 15:14:44 by tglory           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ms_pwd_buff(char *prog_name, char *command_name, int buff_size)
{
	char	*buff;

	buff = ms_mallocw(sizeof(char) * buff_size, "Can't malloc new pwd");
	if (!buff)
		return (NULL);
	if (!getcwd(buff, buff_size) && ((errno == EACCES || errno == EFAULT \
			|| errno == EINVAL || errno == ENOENT)
			|| (errno == ERANGE && buff_size <= 0)))
	{
		ms_print_error(prog_name, command_name);
		return (NULL);
	}
	else if (errno == ERANGE)
	{
		free(buff);
		return (ms_pwd_buff(prog_name, command_name, buff_size * 2));
	}
	return (buff);
}

static t_bool	ms_pwd_create(t_ms_input *input, char *path)
{
	char	*str;

	if (chdir(path) != 0)
	{
		ms_print_error_cmd(input);
		return (FALSE);
	}
	str = ms_pwd_buff(input->cmd->master->name, input->cmd->name, 128);
	if (!str)
		return (FALSE);
	ms_pwd_set(input->cmd->master, str);
	free(str);
	return (TRUE);
}

static t_bool	ms_cd_execute(t_ms_input *input)
{
	input->cmd->master->cmd_ret = 0;
	if (input->args_size == 0)
		return (ms_pwd_create(input, ms_env_get(input->cmd->master, "HOME")));
	if (input->args_size > 1)
	{
		ft_putstr_fd(input->cmd->master->name, 2);
		ft_putendl_fd(": cd: too many arguments", 2);
		return (FALSE);
	}
	if (!ms_file_is_dir(input->args[0]))
	{
		ms_print_error_cmd(input);
		return (FALSE);
	}
	return (ms_pwd_create(input, input->args[0]));
}

t_bool	ms_cmd_cd_register(t_ms_command *cmd)
{
	cmd->execute = &ms_cd_execute;
	return (TRUE);
}
