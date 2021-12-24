/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tglory <tglory@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 05:03:26 by tglory            #+#    #+#             */
/*   Updated: 2021/12/24 17:14:56 by tglory           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	export_print(t_master *master)
{
	t_list	*lst;
	t_list	*cpy;
	t_list	*to_print;

	lst = lst_cpy(master->envs);
	while (lst)
	{
		cpy = lst;
		to_print = lst->next;
		while (to_print)
		{
			if (ft_strcmp(((t_env *)(lst->content))->key,
				((t_env *)(to_print->content))->key) > 0)
				map_swap(lst->content, to_print->content);
			to_print = to_print->next;
		}
		if (((t_env *)(lst->content))->value)
			printf("declare -x %s=\"%s\"\n", ((t_env *)(lst->content))->key,
				((t_env *)(lst->content))->value);
		else
			printf("declare -x %s\n", ((t_env *)(lst->content))->key);
		lst = lst->next;
		free(cpy);
	}
}

static t_bool	ms_export_print_not_valid(char *str)
{
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(str, 2);
	ft_putendl_fd("`: not a valid identifier", 2);
}

static t_bool	ms_export_check_var(t_master *master, t_env *tmp, char *str)
{
	tmp = ms_env_create(str);
	if (!tmp)
	{
		if (!check_var_arg(str))
			ms_export_print_not_valid(str);
		return (FALSE);
	}
	if (!check_var_arg(tmp->key))
	{
		if (*tmp->key)
			ms_export_print_not_valid(tmp->key);
		else
			ms_export_print_not_valid(str);
	}
	else if (!ms_env_add_raw(master, str))
		ms_export_print_not_valid(str);
	return (TRUE);
}

static t_bool	ms_export_print(t_ms_input *input)
{
	int		i;
	t_env	*tmp;

	input->cmd->master->cmd_ret = 0;
	i = 0;
	if (input->args_size == 0)
		export_print(input->cmd->master);
	while (input->args_size > i)
	{
		if (ms_export_check_var(input->cmd->master, tmp, input->args[i]))
			ms_env_free(tmp);
		i++;
	}
	return (TRUE);
}

t_bool	ms_cmd_export_register(t_ms_command *cmd)
{
	cmd->print = &ms_export_print;
	return (TRUE);
}
