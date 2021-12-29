/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblache <jblache@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 05:03:26 by jblache           #+#    #+#             */
/*   Updated: 2021/12/24 19:33:56 by jblache          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_bool	ms_unset_execute(t_ms_input *input)
{
	int	i;

	i = 0;
	while (input->args_size > i)
	{
		if (!check_var_arg(input->args[i]))
		{
			ft_putstr_fd("minishell: unset: `", 2);
			ft_putstr_fd(input->args[i], 2);
			ft_putendl_fd("`: not a valid identifier", 2);
		}
		else
			ms_env_remove(input->cmd->master, input->args[i]);
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
