/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlepart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 16:16:28 by rlepart           #+#    #+#             */
/*   Updated: 2021/03/12 15:43:42 by rlepart          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		ft_only_digit(char *str)
{
	while (str && *str)
	{
		if ((*str < '0' || *str > '9') && *str != '-')
			return (0);
		str++;
	}
	return (1);
}

void	ft_set_exit(t_content *content, char **tab, int pipe)
{
	if (tab[1] && tab[2])
		ft_putstr_fd("exit\nminishell: exit: too many arguments\n", 1);
	else if (!pipe)
	{
		content->exit = 1;
		if (tab[0])
		{
			if (tab[1] && ft_only_digit(tab[1]))
				errno = ft_atoi(tab[1]);
			else if (tab[1])
			{
				printf("minishell: exit: %s: numeric argument required\n",
					tab[1]);
				errno = 255;
			}
		}
	}
}
