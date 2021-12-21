/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_os.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tglory <tglory@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 09:35:36 by tglory            #+#    #+#             */
/*   Updated: 2021/12/21 13:43:26 by tglory           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
// don't free args here
static char	**ms_cmd_os_args(char *command, char **args)
{
	char	**new_args;
	int		i;
	int		size;

	size = -1;
	while (args[++size])
		;
	i = 0;
	if (*args)
	{
		new_args = ms_mallocw(sizeof(char *) * (size + 2),
				"Cannot malloc");
		if (!new_args)
			return (NULL);
		while (args[i])
		{
			new_args[i + 1] = args[i];
			i++;
		}
	}
	else
		new_args = ms_mallocw(sizeof(char *) * 2, "Cannot malloc");
	new_args[0] = command;
	new_args[i + 1] = 0;
	//free(args);
	return (new_args);
}

static void	ms_cmd_os_start(t_master *master,
				char *command, char **args)
{
	char	**temp;

	temp = ms_cmd_os_args(command, args);
	execve(command, temp, ms_env_format(master));
	free(temp);
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
