/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_os.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tglory <tglory@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 09:35:36 by tglory            #+#    #+#             */
/*   Updated: 2021/12/10 05:53:02 by tglory           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_bool	ms_cmd_os_start(t_master *master,
				char *command, char **args)
{
	args--;
	args[0] = command;
	return (ms_cmd_os_run(master, command, args, ms_env_format(master)));
}

static t_bool	ms_cmd_os_search(t_master *master,
				char *command, char **paths, char **args)
{
	char	*name;

	while (*paths)
	{
		name = ft_strjoin_plus(*paths++, "/", command);
		ms_garbage_master_add(master, name, free);
		if (ms_file_can_use(name))
			return (ms_cmd_os_start(master, name, args));
	}
	return (FALSE);
}

t_bool	ms_cmd_os(t_master *master, char *command,
		char **args)
{
	(void)args;
	if (ms_file_can_use(command))
		return (ms_cmd_os_start(master, command, args));
	return (ms_cmd_os_search(master, command, ms_env_path_get(master), args));
}
