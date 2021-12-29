/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblache <jblache@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 13:32:17 by jblache           #+#    #+#             */
/*   Updated: 2021/12/23 17:21:08 by jblache          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ms_env_path_refresh(t_master *master)
{
	char	**paths;
	char	*path;

	path = ms_env_get(master, "PATH");
	if (!path)
		return (NULL);
	paths = ft_split(path, ':');
	if (!paths)
		return (NULL);
	if (!paths[0])
	{
		free(paths);
		return (NULL);
	}
	if (master->paths)
		ms_env_path_free(master);
	master->paths = paths;
	return (master->paths);
}

void	ms_env_path_free(t_master *master)
{
	int	i;

	i = 0;
	if (master->paths)
	{
		while (master->paths[i])
			free(master->paths[i++]);
		free(master->paths);
	}
}

char	**ms_env_path_get(t_master *master)
{
	if (!master->paths)
		return (ms_env_path_refresh(master));
	return (master->paths);
}
