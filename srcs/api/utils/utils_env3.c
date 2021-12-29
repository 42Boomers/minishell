/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tglory <tglory@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 16:41:29 by tglory            #+#    #+#             */
/*   Updated: 2021/12/27 20:47:15 by tglory           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_env_destroy(t_master *master)
{
	ft_lstclear(&master->envs, ms_env_free);
}

void	ms_env_remove(t_master *master, char *key)
{
	ft_lstremove(&master->envs, key, ms_env_key_get, ms_env_free);
	if (ft_isequals(key, "PATH"))
		ms_env_path_refresh(master);
}

t_bool	ms_env_add_raw(t_master *master, char *raw_env)
{
	t_env	*env;

	if (!raw_env)
		return (FALSE);
	env = ms_env_create(raw_env);
	if (ms_env_get_struct(master, env->key))
	{
		ms_env_replace(master, env->key, env->value);
		ms_env_free(env);
		return (TRUE);
	}
	ft_lstadd_back(&master->envs, ft_lstnew(env));
	if (ft_isequals(env->key, "PATH"))
		ms_env_path_refresh(master);
	return (TRUE);
}

void	map_swap(t_env *arg1, t_env *arg2)
{
	t_env		temp;

	temp.key = arg1->key;
	temp.value = arg1->value;
	arg1->key = arg2->key;
	arg1->value = arg2->value;
	arg2->key = temp.key;
	arg2->value = temp.value;
}
