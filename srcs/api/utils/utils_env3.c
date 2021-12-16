/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tglory <tglory@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 16:41:29 by tglory            #+#    #+#             */
/*   Updated: 2021/12/16 16:41:39 by tglory           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_env_destroy(t_master *master)
{
	ft_lstclear(&master->envs, ms_env_free);
}

t_bool	ms_env_remove(t_master *master, char *key)
{
	if (ft_lstremove(master->envs, key, ms_env_key_get, ms_env_free))
		return (FALSE);
	return (TRUE);
}

t_bool	ms_env_add_raw(t_master *master, char *raw_env)
{
	t_env	*env;

	env = ms_env_create(raw_env);
	if (ms_env_get_struct(master, env->key))
	{
		ms_env_replace(master, env->key, env->value);
		ms_env_free(env);
		return (TRUE);
	}
	ft_lstadd_back(&master->envs,
		ft_lstnew(env));
	return (TRUE);
}
