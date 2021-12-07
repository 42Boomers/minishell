/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sylducam <sylducam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 18:10:36 by tglory            #+#    #+#             */
/*   Updated: 2021/12/07 15:58:09 by sylducam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	ms_env_init(t_master *master, char **raw_envs)
{
	int		i;

	i = 0;
	while (raw_envs[i]) // syl : i = lines ? envs is structured by lines ?
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

char	*ms_env_get(t_master *master, char *key)
{
	int		i;
	char	*tmp;

	i = 0;
	while (i < master->envs_size)
	{
		tmp = master->envs[i][0];
		if (!ft_strncmp(tmp, key, ft_strlen(tmp) + 1))
			return (master->envs[i][1]);
		i++;
	}
	// return (getenv(key)); //-> get env from system
	return (NULL);
}

char	**ms_env_set(t_master *master, char *key, char *value)
{
	int		i;
	char	*tmp;

	i = 0;
	while (i < master->envs_size)
	{
		tmp = master->envs[i][0];
		if (!ft_strncmp(tmp, key, ft_strlen(tmp) + 1))
		{
			free(master->envs[i][1]);
			master->envs[i][1] = ft_strdup(value);
			return (&master->envs[i][1]);
		}
		i++;
	}
	return (NULL);
}

char	**ms_env_format(t_master *master)
{
	int		i;
	char	**out;

	i = 0;
	out = malloc(sizeof(char *) * (master->envs_size + 1));
	if (!out)
		return (NULL);
	while (i < master->envs_size)
	{
		out[i] = ft_strjoin_plus(master->envs[i][0], "=", master->envs[i][1]);
		ms_garbage_default_add(master, out[i], free);
		i++;
	}
	out[i] = NULL;
	ms_garbage_default_add(master, out, free);
	return (out);
}
