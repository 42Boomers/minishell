/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblache <jblache@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 14:58:52 by jblache           #+#    #+#             */
/*   Updated: 2021/12/29 14:59:14 by jblache          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	export_no_value(t_master *master, char *str)
{
	t_env	*env;
	t_list	*lst;

	env = ms_mallocw(sizeof(t_env), "Can't malloc t_env");
	if (!env)
		return ;
	env->key = ft_strdup(str);
	env->value = NULL;
	lst = ft_lstnew(env);
	ft_lstadd_back(&master->envs, lst);
}
