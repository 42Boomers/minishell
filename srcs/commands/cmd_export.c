/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tglory <tglory@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 05:03:26 by tglory            #+#    #+#             */
/*   Updated: 2021/12/21 13:14:37 by tglory           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_bool	ms_export_analyze(t_ms_input *input)
{
	(void)input;
	return (TRUE);
}

int	check_export_arg(char *arg)
{
	int	i;

	if (!ft_isalpha(arg[0]) && arg[0] != '_')
		return (FALSE);
	i = 0;
	while (arg[i])
	{
		if (!ft_isalnum(arg[i]) && arg[i] != '_')
			return (FALSE);
		i++;
	}
	return (TRUE);
}

static t_bool	ms_export_execute(t_ms_input *input)
{
	int		i;
	t_env	*tmp;

	input->cmd->master->cmd_ret = 0;
	i = 0;
	while (input->args_size > i)
	{
		tmp = ms_env_create(input->args[i]);
		if (!tmp)
		{
			fprintf(stderr, "minishell: export: `%s`: not a valid identifier",
				input->args[i]);
			continue ;
		}
		if (!check_export_arg(tmp->key))
		{
			ft_putstr_fd("minishell: export: `", 2);
			if (*tmp->key)
				ft_putstr_fd(tmp->key, 2);
			else
				ft_putstr_fd(input->args[i], 2);
			ft_putendl_fd("`: not a valid identifier", 2);
		}
		else if (!ms_env_add_raw(input->cmd->master, input->args[i]))
			fprintf(stderr, "minishell: export: `%s`: not a valid identifier",
				input->args[i]);
		ms_env_free(tmp);
		i++;
	}
	return (TRUE);
}

static t_bool	ms_export_print(t_ms_input *input)
{
	(void)input;
	return (TRUE);
}

t_bool	ms_cmd_export_register(t_ms_command *cmd)
{
	cmd->analyze = &ms_export_analyze;
	cmd->execute = &ms_export_execute;
	cmd->print = &ms_export_print;
	return (TRUE);
}
