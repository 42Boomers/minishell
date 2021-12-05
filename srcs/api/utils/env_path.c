/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tglory <tglory@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 13:32:17 by tglory            #+#    #+#             */
/*   Updated: 2021/12/05 13:36:30 by tglory           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ms_env_path_refresh(t_master *master)
{
	char	**paths;
	char	*path;
	int		i;

	path = ms_env_get(master, "PATH");
	if (!path)
		return (FALSE);
	paths = ft_split(path, ':');
	if (!paths)
		return (FALSE);
	i = 0;
	while (paths[i])
		ms_garbage_default_add(master, paths[i++], free);
	ms_garbage_default_add(master, paths, free);
	if (!paths[0])
	{
		free(paths);
		return (FALSE);
	}
	master->paths = paths;
	return (master->paths);
}

char	**ms_env_path_get(t_master *master)
{
	if (!master->paths)
		return (ms_env_path_refresh(master));
	return (master->paths);
}
