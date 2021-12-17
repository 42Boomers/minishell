/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tglory <tglory@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 05:03:26 by tglory            #+#    #+#             */
/*   Updated: 2021/12/17 00:14:04 by tglory           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_bool	ms_unset_execute(t_ms_input *input)
{
	int	i;

	i = 0;
	while (i < input->args_size)
	{
		ms_env_remove(input->cmd->master, input->args[i]);
		if (ft_isequals(input->args[i], "PATH"))
			ms_env_path_refresh(input->cmd->master);
		i++;
	}
	return (TRUE);
}

t_bool	ms_cmd_unset_register(t_ms_command *cmd)
{
	cmd->master->cmd_ret = 0;
	cmd->execute = &ms_unset_execute;
	return (TRUE);
}
