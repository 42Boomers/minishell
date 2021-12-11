/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tglory <tglory@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 18:10:36 by tglory            #+#    #+#             */
/*   Updated: 2021/12/11 01:48:05 by tglory           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_env	*ms_env_create_basic(char *key, char *value)
{
	t_env	*envs;

	envs = malloc(sizeof(t_env));
	if (!envs)
		return (NULL);
	envs->key = key;
	envs->value = value;
	return (envs);
}

static t_env	*ms_env_create(char *raw_envs)
{
	t_env	*env;
	char	**env_array;

	env_array = ft_strtrunc(raw_envs, '=');
	env = ms_env_create_basic(env_array[0], env_array[1]);
	free(env_array);
	return (env);
}

static char	*ms_env_key_get(void *arg)
{
	t_env	*envs;

	envs = arg;
	return (envs->key);
}

static void	ms_env_free(void *arg)
{
	t_env	*env;

	env = arg;
	free(env->key);
	free(env->value);
	free(env);
}

static t_env	*ms_env_get_struct(t_master *master, char *key)
{
	return (ft_lstget(master->envs, key, ms_env_key_get));
}

void	ms_env_destroy(t_master *master)
{
	ft_lstclear(&master->envs, ms_env_free);
}

t_bool	ms_env_init(t_master *master, char **raw_envs)
{
	int		i;

	i = 0;
	while (raw_envs[i])
		ft_lstadd_back(&master->envs,
			ft_lstnew(ms_env_create(raw_envs[i++])));
	return (TRUE);
}

char	*ms_env_get(t_master *master, char *key)
{
	t_env	*env;

	env = ms_env_get_struct(master, key);
	if (!env)
		return (NULL);
	return (env->value);
}

t_bool	ms_env_remove(t_master *master, char *key)
{
	if (ft_lstremove(master->envs, key, ms_env_key_get, ms_env_free))
		return (FALSE);
	return (TRUE);
}

t_bool	ms_env_add_raw(t_master *master, char *env)
{
	ft_lstadd_back(&master->envs,
		ft_lstnew(ms_env_create(env)));
	return (TRUE);
}

t_bool	ms_env_add(t_master *master, char *key, char *value)
{
	if (ms_env_get_struct(master, key))
		return (FALSE); // TODO ms_env_replace
	ft_lstadd_back(&master->envs,
		ft_lstnew(ms_env_create_basic(key, value)));
	return (TRUE);
}

char	**ms_env_replace(t_master *master, char *key, char *value)
{
	t_env	*env;
	char	*tmp;

	env = ms_env_get_struct(master, key);
	if (!env)
		return (NULL);
	tmp = env->value;
	env->value = ft_strdup(value);
	if (!env->value)
		return (NULL);
	free(tmp);
	return (&env->value);
}

char	**ms_env_format(t_master *master)
{
	int		i;
	char	**out;
	t_list	*lst;
	t_env	*env;

	i = 0;
	lst = master->envs;
	out = malloc(sizeof(char *) * (ft_lstsize(lst) + 1));
	if (!out)
		return (NULL);
	while (lst)
	{
		env = lst->content;
		out[i] = ft_strjoin_plus(env->key, "=", env->value);
		ms_garbage_master_add(master, out[i], free);
		i++;
		lst = lst->next;
	}
	out[i] = NULL;
	ms_garbage_master_add(master, out, free);
	return (out);
}
