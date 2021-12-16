/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tglory <tglory@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 13:39:53 by tglory            #+#    #+#             */
/*   Updated: 2021/12/16 22:09:02 by tglory           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	ms_file_can_use(char *fname)
{
	return (!access(fname, F_OK));
}

t_bool	ms_file_is_dir(char *dname)
{
	DIR		*dir;

	dir = opendir(dname);
	if (dir)
	{
		closedir(dir);
		return (TRUE);
	}
	else
		return (FALSE);
}

char	*ms_pwd(t_master *master)
{
	char	*env;

	env = ms_env_get(master, "PWD");
	if (!env)
		return (NULL);
	master->pwd = &env;
	return (env);
}

void	ms_pwd_set(t_master *master, char *new_pwd)
{
	// master->old_pwd = ft_strdup(master->pwd);
	ms_env_replace(master, "PWD", new_pwd);
	master->pwd = ms_env_replace(master, "PWD", new_pwd);
}
