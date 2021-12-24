/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sylducam <sylducam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 05:03:26 by tglory            #+#    #+#             */
/*   Updated: 2021/12/24 16:52:22 by sylducam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_list	*lst_cpy(t_list *lst)
{
	t_list	*cpy;

	while (lst)
	{
		ft_lstadd_back(&cpy, ft_lstnew(lst->content));
		lst = lst->next;
	}
	return (cpy);
}

static void	map_swap(t_env *arg1, t_env *arg2)
{
	t_env	temp;

	temp.key = arg1->key;
	temp.value = arg1->value;
	arg1->key = arg2->key;
	arg1->value = arg2->value;
	arg2->key = temp.key;
	arg2->value = temp.value;
}

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
			if (ft_strcmp(((t_env *)(lst->content))->key, \
				((t_env *)(to_print->content))->key) > 0)
				map_swap(lst->content, to_print->content);
			to_print = to_print->next;
		}
		if (((t_env *)(lst->content))->value)
			printf("declare -x %s=\"%s\"\n", ((t_env *)(lst->content))->key, \
			((t_env *)(lst->content))->value);
		else
			printf("declare -x %s\n", ((t_env *)(lst->content))->key);
		lst = lst->next;
		free(cpy);
	}
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
		tmp = ms_env_create(input->args[i]);
		if (!tmp)
		{
			if (!check_var_arg(input->args[i]))
			{
				ft_putstr_fd("minishell: export: `", 2);
				ft_putstr_fd(input->args[i], 2);
				ft_putendl_fd("`: not a valid identifier", 2);
			}
			i++;
			continue ;
		}
		if (!check_var_arg(tmp->key))
		{
			ft_putstr_fd("minishell: export: `", 2);
			if (*tmp->key)
				ft_putstr_fd(tmp->key, 2);
			else
				ft_putstr_fd(input->args[i], 2);
			ft_putendl_fd("`: not a valid identifier", 2);
		}
		else if (!ms_env_add_raw(input->cmd->master, input->args[i]))
		{
			ft_putstr_fd("minishell: export: `", 2);
			ft_putstr_fd(input->args[i], 2);
			ft_putendl_fd("`: not a valid identifier", 2);
		}
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
