/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperez <bperez@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 05:24:06 by bperez            #+#    #+#             */
/*   Updated: 2021/11/25 06:48:08 by bperez           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	replace_split_spaces(char *command)
{
	int		quote;
	int		double_quote;	

	quote = 0;
	double_quote = 0;
	while (*command)
	{
		check_quotes(*command, &quote, &double_quote);
		if (*command == ' ' && quote == 0 && double_quote == 0)
			*command = 1;
		command++;
	}
}

int	get_variable_name_length(char *command, int i)
{
	int	var_name_length;

	var_name_length = 0;
	while (command[i + var_name_length])
	{
		if (!ft_isalnum(command[i + var_name_length]))
			break ;
		var_name_length++;
	}
	return (var_name_length);
}

int	expand_tilde(t_command *command, char **split_cmd, int i)
{
	char	*var;
	char	*new_command;

	var = get_current_env(command->shell, "HOME");
	if (var[0] != '\0')
	{
		new_command = ft_substr(*split_cmd, 0, i);
		new_command = ft_tmp(new_command, ft_strjoin(new_command, var));
		var = ft_substr(*split_cmd, i + 1, ft_strlen(*split_cmd + i + 1));
		if (var)
		{
			new_command = ft_tmp(new_command, ft_strjoin(new_command, var));
			if (new_command)
			{
				free(*split_cmd);
				*split_cmd = new_command;
				return (SUCCESS);
			}
		}
	}
	return (ERROR);
}

int	expand_env_variable(t_command *command, char **split_command, int i)
{
	char	*var;
	int		var_name_length;
	char	*new_command;

	var_name_length = get_variable_name_length(*split_command, i);
	var = ft_substr(*split_command, i, var_name_length);
	if (var)
	{
		var = ft_tmp(var, get_current_env(command->shell, var));
		new_command = ft_substr(*split_command, 0, i - 1);
		new_command = ft_tmp(new_command, ft_strjoin(new_command, var));
		i += var_name_length;
		var = ft_substr(*split_command, i, ft_strlen(*split_command + i));
		if (var)
		{
			new_command = ft_tmp(new_command, ft_strjoin(new_command, var));
			if (new_command)
			{
				free(*split_command);
				*split_command = new_command;
				return (SUCCESS);
			}
		}
	}
	return (ERROR);
}

int	expand_exit_status_variable(t_command *command, char **split_cmd, int i)
{
	char	*exit_status;
	char	*new_command;
	int		strlen;

	exit_status = ft_itoa(command->shell->last_exit_status);
	if (exit_status)
	{
		new_command = ft_substr(*split_cmd, 0, i);
		new_command = ft_tmp(new_command, ft_strjoin(new_command, exit_status));
		strlen = ft_strlen(*split_cmd);
		*split_cmd = ft_tmp(*split_cmd, ft_substr(*split_cmd, i + 2, strlen));
		new_command = ft_tmp(new_command, ft_strjoin(new_command, *split_cmd));
		if (new_command)
		{
			free(*split_cmd);
			*split_cmd = new_command;
			return (SUCCESS);
		}
	}
	return (ERROR);
}
