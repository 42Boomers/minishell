/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblache <jblache@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 18:10:36 by jblache           #+#    #+#             */
/*   Updated: 2021/12/27 21:11:33 by jblache          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*ms_env_create_basic(char *key, char *value)
{
	t_env	*env;

	env = ms_mallocw(sizeof(t_env), "Can't malloc t_env");
	if (!env)
		return (NULL);
	env->key = key;
	env->value = value;
	return (env);
}

t_env	*ms_env_create(char *raw_envs)
{
	t_env	*env;
	char	**env_array;

	env_array = ft_strtrunc(raw_envs, '=');
	if (!env_array)
		return (NULL);
	env = ms_env_create_basic(env_array[0], env_array[1]);
	if (!env)
		return (NULL);
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

	if (!arg)
		return ;
	env = arg;
	if (env->key)
		free(env->key);
	if (env->value)
		free(env->value);
	if (env)
		free(env);
}

t_env	*ms_env_get_struct(t_master *master, char *key)
{
	return (ft_lstget(master->envs, key, ms_env_key_get));
}
