/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tglory <tglory@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 22:36:30 by tglory            #+#    #+#             */
/*   Updated: 2021/12/28 17:52:07 by tglory           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ms_prefix_short(char *pwd, char *home)
{
	int		i;

	i = 0;
	while (*pwd && home[i] && *pwd == home[i])
	{
		i++;
		pwd++;
	}
	if (home[i] || *(pwd - 1) != home[i - 1])
		return (NULL);
	return (ft_strjoin("~", pwd));
}

char	*ms_prefix_get_custom(t_master *master)
{
	char	*data;
	char	*pwd;
	char	*home;

	data = NULL;
	pwd = ms_pwd(master);
	if (!pwd)
		return (ft_strdup(master->name));
	home = ms_env_get(master, "HOME");
	if (home)
	{
		if (ft_isequals(pwd, home))
			return (ft_strdup("~"));
		data = ms_prefix_short(pwd, home);
	}
	if (!data)
		return (ft_strdup(pwd));
	return (data);
}

char	*ms_prefix_get(t_master *master)
{
	char	*color;
	char	*data;
	char	*prefix;

	if (!master->last_status)
		color = "\e[0;32m\e[1m➜\e[36m  ";
	else
		color = "\e[0;31m\e[1m➜\e[36m  ";
	data = ms_prefix_get_custom(master);
	prefix = ft_strjoin_plus(color, data, " > \e[0;33m");
	free(data);
	return (prefix);
}
