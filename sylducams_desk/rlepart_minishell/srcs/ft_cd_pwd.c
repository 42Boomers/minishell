/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_pwd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlepart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 15:24:04 by rlepart           #+#    #+#             */
/*   Updated: 2021/02/19 15:58:48 by rlepart          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_pwd(void)
{
	char	*buf;

	buf = getcwd(NULL, 100);
	if (buf)
	{
		ft_putstr_fd(buf, 1);
		ft_putstr_fd("\n", 1);
		free(buf);
	}
	else
	{
		ft_putstr_fd(strerror(errno), 1);
	}
}

void	ft_cd(t_content *content, char *path, int pipe)
{
	int		n;
	char	buf[10000];

	if (pipe)
		return ;
	getcwd(buf, 9999);
	buf[9999] = '\0';
	if (path && *path)
		n = chdir(path);
	else if (ft_get_env(content, "HOME"))
		n = chdir(ft_get_env(content, "HOME"));
	else
	{
		ft_putstr_fd("cd: HOME not set\n", 1);
		errno = 1;
		return ;
	}
	if (n == -1)
	{
		printf("minishell: cd: %s: %s\n", path, strerror(errno));
		errno = 1;
	}
	else
		ft_edit_env(content, "OLDPWD", ft_strjoin("OLDPWD=", buf));
}
