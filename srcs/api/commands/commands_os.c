/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_os.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tglory <tglory@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 09:35:36 by tglory            #+#    #+#             */
/*   Updated: 2021/12/05 13:46:03 by tglory           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_bool	ms_cmd_os_start(t_master *master,
				char *command)
{
	char	**argv;

	argv = ms_malloc_master(master, sizeof(char *) * 2);
	argv[0] = command;
	argv[1] = NULL;
	return (ms_cmd_os_run(master, command, argv, ms_env_format(master)));
}

static t_bool	ms_cmd_os_search(t_master *master,
				char *command, char **paths)
{
	char	*name;

	while (*paths)
	{
		name = ft_strjoin_plus(*paths++, "/", command);
		ms_garbage_default_add(master, name, free);
		if (ms_file_can_use(name))
			return (ms_cmd_os_start(master, name));
	}
	return (FALSE);
}

t_bool	ms_cmd_os(t_master *master, char *command,
		char **args)
{
	(void)args;
	if (ms_file_can_use(command))
		return (ms_cmd_os_start(master, command));
	return (ms_cmd_os_search(master, command, ms_env_path_get(master)));
}