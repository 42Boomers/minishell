/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_display.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlepart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 15:33:29 by rlepart           #+#    #+#             */
/*   Updated: 2021/02/19 17:24:12 by rlepart          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_echo(t_content *content, char **buf)
{
	int	n;

	n = 0;
	while (*buf && (*buf)[0] == '-' && (*buf)[1] == 'n' && (*buf)[2] == '\0')
	{
		buf++;
		n = 1;
	}
	while (buf && *buf)
	{
		content->buf = ft_join_free(content->buf, *buf, 2);
		buf++;
		if (*buf)
			content->buf = ft_join_free(content->buf, " ", 2);
	}
	if (n == 0)
		content->buf = ft_join_free(content->buf, "\n", 2);
	ft_putstr_fd(content->buf, 1);
	free(content->buf);
	content->buf = NULL;
	errno = 0;
}

void	ft_print_env(t_content *content, char **env)
{
	while (env && *env)
	{
		if ((*env)[0] == '_' && (*env)[1] == '=')
			content->buf = ft_join_free(content->buf, "_=env", 2);
		else
			content->buf = ft_join_free(content->buf, *env, 2);
		content->buf = ft_join_free(content->buf, "\n", 2);
		env++;
	}
	ft_putstr_fd(content->buf, 1);
	free(content->buf);
	content->buf = NULL;
}
