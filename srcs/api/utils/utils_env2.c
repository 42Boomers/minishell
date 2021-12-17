/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tglory <tglory@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 16:37:32 by tglory            #+#    #+#             */
/*   Updated: 2021/12/17 00:56:18 by tglory           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

t_bool	ms_env_add(t_master *master, char *key, char *value)
{
	if (ms_env_get_struct(master, key))
	{
		ms_env_replace(master, key, value);
		return (TRUE);
	}
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
	if (ft_isequals(env->key, "PATH"))
		ms_env_path_refresh(master);
	return (&env->value);
}
