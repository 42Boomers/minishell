/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tglory <tglory@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 13:39:53 by tglory            #+#    #+#             */
/*   Updated: 2021/12/21 12:35:51 by tglory           ###   ########lyon.fr   */
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
	if (!dir)
		return (FALSE);
	closedir(dir);
	return (TRUE);
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
	ms_env_add(master, "OLDPWD", ms_pwd(master));
	ms_env_add(master, "PWD", new_pwd);
	ms_pwd(master);
}
