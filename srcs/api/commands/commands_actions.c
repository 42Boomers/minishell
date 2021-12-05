/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_actions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tglory <tglory@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 02:47:22 by tglory            #+#    #+#             */
/*   Updated: 2021/12/05 02:52:07 by tglory           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	ms_launch_at_start(t_master *master)
{
	char	*command;
	char	**args;
	char	**ag;

	if (master->av <= 1)
		return (FALSE);
	ag = master->ag;
	command = *++ag;
	args = NULL;
	if (master->av > 2)
	{
		ag++;
		args = ag;
	}
	ms_cmd_launch(master, command, args, master->av - 1);
	return (TRUE);
}
