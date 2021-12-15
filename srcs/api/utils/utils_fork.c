/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_fork.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrozniec <mrozniec@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 13:04:22 by mrozniec          #+#    #+#             */
/*   Updated: 2021/12/15 13:04:22 by mrozniec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_error_pipe(int pip_end[2])
{
	if (pipe(pip_end) == -1)
	{
		ft_println_red("Error > An error has occured while pipe creation");
		return (-1);
	}
	return (0);
}

void	ms_check_redir(char **command, char **args)
{
	char	*temp;

	temp = NULL;
	if ((ft_strcmp(*command, "<") == 0) || (ft_strcmp(*command, "<<") == 0) || \
	(ft_strcmp(*command, ">") == 0) || (ft_strcmp(*command, ">>") == 0))
	{
		temp = *command;
		*command = args[1];
		args[1] = args[0];
		args[0] = temp;
	}
}
