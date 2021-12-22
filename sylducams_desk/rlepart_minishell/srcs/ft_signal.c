/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlepart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 16:16:28 by rlepart           #+#    #+#             */
/*   Updated: 2021/02/21 17:18:01 by rlepart          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_sigquit(int signal, void *content)
{
	static t_content	*save = NULL;

	signal = 0;
	if (!save)
		save = content;
	else if (save->pid > 0)
	{
		kill(save->pid, SIGQUIT);
		ft_putstr_fd("Quit : 3\n", 1);
	}
}

void	ft_sigint(int signal, void *content)
{
	static t_content	*save = NULL;

	signal = 0;
	if (!save)
		save = content;
	else
	{
		write(1, "\n", 1);
		if (save->pid == -1)
		{
			ft_putstr_fd("minishell -> ", 1);
		}
		else if (save->pid)
		{
			kill(save->pid, SIGINT);
		}
	}
}
