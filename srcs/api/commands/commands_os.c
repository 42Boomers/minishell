/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_os.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tglory <tglory@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 09:35:36 by tglory            #+#    #+#             */
/*   Updated: 2021/12/17 08:21:25 by tglory           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ms_cmd_os_start(t_master *master,
				char *command, char **args)
{
	args--;
	args[0] = command;
	execve(command, args, ms_env_format(master));
}

static t_bool	ms_cmd_os_search(t_master *master,
				char *command, char **paths, char **args)
{
	char	*name;

	while (*paths)
	{
		name = ft_strjoin_plus(*paths++, "/", command);
		if (ms_file_can_use(name))
		{
			ms_cmd_os_start(master, name, args);
			free(name);
			break ;
		}
		free(name);
	}
	return (FALSE);
}

t_bool	ms_cmd_os(t_master *master, char *command,
		char **args)
{
	if (ms_file_can_use(command))
	{
		ms_cmd_os_start(master, command, args);
		return (FALSE);
	}
	return (ms_cmd_os_search(master, command, ms_env_path_get(master), args));
}
