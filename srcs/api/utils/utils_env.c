/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tglory <tglory@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 18:10:36 by tglory            #+#    #+#             */
/*   Updated: 2021/12/16 16:49:25 by tglory           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*ms_env_create_basic(char *key, char *value)
{
	t_env	*envs;

	envs = malloc(sizeof(t_env));
	if (!envs)
		return (NULL);
	envs->key = key;
	envs->value = value;
	return (envs);
}

t_env	*ms_env_create(char *raw_envs)
{
	t_env	*env;
	char	**env_array;

	env_array = ft_strtrunc(raw_envs, '=');
	env = ms_env_create_basic(env_array[0], env_array[1]);
	free(env_array);
	return (env);
}

char	*ms_env_key_get(void *arg)
{
	t_env	*envs;

	envs = arg;
	return (envs->key);
}

void	ms_env_free(void *arg)
{
	t_env	*env;

	env = arg;
	free(env->key);
	free(env->value);
	free(env);
}

t_env	*ms_env_get_struct(t_master *master, char *key)
{
	return (ft_lstget(master->envs, key, ms_env_key_get));
}
