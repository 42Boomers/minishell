/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tglory <tglory@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 21:11:17 by tglory            #+#    #+#             */
/*   Updated: 2021/12/05 01:27:54 by tglory           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Analyze argument of command ENV.
 * Gets the environment variables.
 * @param input
 * @return t_bool
 */
t_bool	ms_env_analyze(t_ms_input *input)
{
	input->data = ms_malloc(&input->garbage, sizeof(t_ms_cmd_env));
	if (!input->data)
		return (FALSE);
	((t_ms_cmd_env *) input->data)->raw_envs = input->cmd->master->envs;
	return (TRUE);
}

/**
 * @brief Execute command ENV.
 * Reads the environment variables and set in ur format.
 * @param input
 * @return t_bool
 */
t_bool	ms_env_execute(t_ms_input *input)
{
	t_ms_cmd_env	*env_cmd;
	char			**raw_envs;
	char			***envs;
	int				i;

	env_cmd = (t_ms_cmd_env*) input->data;
	raw_envs = env_cmd->raw_envs;
	i = 0;
	while (raw_envs[i])
		i++;
	env_cmd->envs_size = i;
	env_cmd->envs = ms_malloc(&input->garbage, sizeof(char**) * i);
	envs = env_cmd->envs;
	i = -1;
	while (raw_envs[++i])
	{
		envs[i] = ft_strtrunc(raw_envs[i], '=');
	}
	return (TRUE);
}

/**
 * @brief Print command ENV
 * Print all the environment variable.
 * @param input
 * @return t_bool
 */
t_bool	ms_env_print(t_ms_input *input)
{
	t_ms_cmd_env	*env_cmd;
	char			***envs;
	int				i;

	env_cmd = (t_ms_cmd_env*) input->data;
	envs = env_cmd->envs;
	i = 0;
	while (i < env_cmd->envs_size)
	{
		printf("%s=%s\n", envs[i][0], envs[i][1]);
		free(envs[i][0]);
		free(envs[i][1]);
		free(envs[i]);
		i++;
	}
	return (TRUE);
}

/**
 * @brief Register theses functions has command
 * To execute a command in a universal way,
 * we must give it 3 functions
 * @param cmd
 * @return t_bool
 */
t_bool	ms_cmd_env_register(t_ms_command *cmd)
{
	cmd->analyze = &ms_env_analyze;
	cmd->execute = &ms_env_execute;
	cmd->print = &ms_env_print;
	return (TRUE);
}
