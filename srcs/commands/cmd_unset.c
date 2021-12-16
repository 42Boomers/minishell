/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tglory <tglory@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 05:03:26 by tglory            #+#    #+#             */
/*   Updated: 2021/12/16 16:15:38 by tglory           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_bool	ms_unset_analyze(t_ms_input *input)
{
	(void)input;
	return (TRUE);
}
/*
int	ms_strcmp(char *str1, char *str2)
{
	int i;

	i = 0;
	while (str1[i] && str2[i] && str1[i] == str2[i])
		i++;
	if (!str1[i] && !str2[i])
		return (0);
	if (str1[i] && str2[i])
		return (str1[i] - str2[i]);
	if (str1[i])
		return (str1[i]);
	return (str2[i]);
}

static t_bool	env_recreate(t_master *master, int to_skip)
{
	int		i;
	int		j;
	char	***new_envs;

	master->envs_size--;
	new_envs = malloc(sizeof(char **) * master->envs_size);
	if (!new_envs)
		return (FALSE);
	i = 0;
	while (i < master->envs_size)
	{
		new_envs[i] = malloc(sizeof(char *) * 2);
		i++;
	}
	i = -1;
	j = 0;
	while (++i < master->envs_size + 1)
	{
		printf("%d\n", master->envs_size);
		if (i == to_skip)
			continue;
		new_envs[j][0] = ft_strdup(master->envs[i][0]);
		new_envs[j][1] = ft_strdup(master->envs[i][1]);
		i++;
		j++;
	}
	master->envs = new_envs;
	//ici le pointeur new_envs remplace l'ancien master->env, sans free, il faut corriger les leaks
	return (TRUE);
}*/

static t_bool	ms_unset_execute(t_ms_input *input)
{
	int	j;

	j = 0;
	while (j < input->args_size)
	{
		if (!ms_env_remove(input->cmd->master, input->args[j]))
			printf("Can't remove %s\n", input->args[j]);
		// i = 0;
		// while (i < input->cmd->master->envs_size)
		// {
		// 	if (!ft_strcmp(input->cmd->master->envs[i][0], input->args[j]))
		// 	{
		// 		env_recreate(input->cmd->master, i);
		// 		break;
		// 	}
		// 	i++;
		// }
		j++;
	}
	return (TRUE);
}

static t_bool	ms_unset_print(t_ms_input *input)
{
	(void)input;
	return (TRUE);
}

t_bool	ms_cmd_unset_register(t_ms_command *cmd)
{
	cmd->analyze = &ms_unset_analyze;
	cmd->execute = &ms_unset_execute;
	cmd->print = &ms_unset_print;
	return (TRUE);
}
