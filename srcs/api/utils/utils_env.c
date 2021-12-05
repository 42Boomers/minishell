/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tglory <tglory@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 18:10:36 by tglory            #+#    #+#             */
/*   Updated: 2021/12/05 02:56:11 by tglory           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	ms_env_init(t_master *master, char **raw_envs)
{
	int		i;

	i = 0;
	while (raw_envs[i])
		i++;
	master->envs_size = i;
	master->envs = ms_malloc_master(master, sizeof(char **) * i);
	if (!master->envs)
		return (FALSE);
	i = -1;
	while (raw_envs[++i])
	{
		master->envs[i] = ft_strtrunc(raw_envs[i], '=');
		ms_garbage_default_add(master, master->envs[i][0], free);
		ms_garbage_default_add(master, master->envs[i][1], free);
		ms_garbage_default_add(master, master->envs[i], free);
	}
	return (TRUE);
}

char	**ms_env_get(t_master *master, char *key)
{
	int		i;
	char	*tmp;

	i = 0;
	while (i < master->envs_size)
	{
		tmp = master->envs[i][0];
		if (!ft_strncmp(tmp, key, ft_strlen(tmp) + 1))
			return (master->envs[i]);
		i++;
	}
	return (NULL);
}

t_bool	ms_env_set(t_master *master, char *key, char *value)
{
	char	**env;

	env = ms_env_get(master, key);
	if (!env)
		return (FALSE);
	env[1] = value;
	return (TRUE);
}

char	*ms_pwd(t_master *master)
{
	char	**env;

	env = ms_env_get(master, "PWD");
	if (!env)
		return (NULL);
	return (env[1]);
}
