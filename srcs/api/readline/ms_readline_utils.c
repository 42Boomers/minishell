/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_readline_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrozniec <mrozniec@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 00:32:08 by jblache           #+#    #+#             */
/*   Updated: 2021/12/24 00:32:45 by mrozniec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pipe_check(char **args)
{
	int	i;

	i = -1;
	while (args[++i])
	{
		if (ft_strcmp(args[i], "|") == 0)
		{
			args[i] = NULL;
			if (!args[i + 1])
				return (0);
			if (ft_strcmp(args[i + 1], "|") == 0)
				return (-(i + 1));
			return (i + 1);
		}
	}
	return (0);
}
