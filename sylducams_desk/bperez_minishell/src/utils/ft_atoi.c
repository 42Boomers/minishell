/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: neben <neben@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 08:44:11 by ngeschwi          #+#    #+#             */
/*   Updated: 2021/11/29 13:20:44 by neben            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_white_space(char str)
{
	if (str == '\t' || str == '\n'
		|| str == '\v' || str == '\f'
		|| str == '\r' || str == ' ')
		return (1);
	else
		return (0);
}

int	ft_atoi(const char *str)
{
	int		i;
	int		total;
	int		nbrless;

	nbrless = 1;
	i = 0;
	total = 0;
	while (str[i])
	{
		if (!ft_white_space(str[i]))
			break ;
		i++;
	}
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			nbrless = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		total = total * 10 + (str[i] - '0');
		i++;
	}
	return (total * nbrless);
}
