/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_actions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tglory <tglory@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 02:47:22 by tglory            #+#    #+#             */
/*   Updated: 2021/12/10 23:50:25 by tglory           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	ms_launch_at_start(t_master *master)
{
	char	*command;
	char	**args;

	if (master->ac <= 1)
		return (FALSE);
	command = master->av[1];
	if (master->ac > 2)
	{
		args = master->av;
		args += 2;
	}
	else
		args = NULL;
	ms_cmd_launch(master, command, args, master->ac - 2);
	return (TRUE);
}
