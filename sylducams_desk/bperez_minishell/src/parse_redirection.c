/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngeschwi <nathan.geschwind@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 05:19:57 by bperez            #+#    #+#             */
/*   Updated: 2021/11/25 16:47:22 by bperez           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_redirection_type(t_command *cmd, char *command)
{
	int	check_redirection;

	if (*command == '<')
	{
		cmd->redirection_in = REDIRECTION_INPUT;
		check_redirection = ft_strcmp(command, "<<");
		if (check_redirection == 0)
			cmd->redirection_in = REDIRECTION_DINPUT;
		return (cmd->redirection_in);
	}
	else
	{
		cmd->redirection_out = REDIRECTION_OUTPUT;
		check_redirection = ft_strcmp(command, ">>");
		if (check_redirection == 0)
			cmd->redirection_out = REDIRECTION_DOUTPUT;
		return (cmd->redirection_out);
	}
}

void	free_redirection(int current_type, char **split_command)
{
	int	i;

	i = 0;
	free(*split_command);
	if (current_type != REDIRECTION_DINPUT)
		free(*(split_command + 1));
	while (split_command[i + 2])
	{
		split_command[i] = split_command[i + 2];
		i++;
	}
	split_command[i] = NULL;
	split_command[i + 1] = NULL;
}

int	parse_redirection_argument(int type, t_command *cmd, char **split_cmd)
{
	int	i;
	int	quote;
	int	double_quote;

	if (*split_cmd)
	{
		i = 0;
		quote = 0;
		double_quote = 0;
		while (*split_cmd && i < ft_strlen(*split_cmd))
		{
			if (interpret_quotes(split_cmd, &i, &quote, &double_quote))
				return (ERROR);
			if (type != REDIRECTION_DINPUT && quote == 0 && \
				(*split_cmd)[i] == '$' && ft_isalnum((*split_cmd)[i + 1]))
			{
				if (expand_env_variable(cmd, split_cmd, i + 1) == ERROR)
					return (ERROR);
				i -= -1;
			}
			i++;
		}
		return (SUCCESS);
	}
	return (ERROR);
}

int	are_there_redirections_in_argument(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] == '>' || arg[i] == '<')
			return (1);
		i++;
	}
	return (0);
}

int	parse_redirection(t_command *command, char **split_command)
{
	int		current_type;
	int		ret;

	ret = ERROR;
	current_type = get_redirection_type(command, *split_command);
	if (*(split_command + 1) && \
		!are_there_redirections_in_argument(*(split_command + 1)) && \
		parse_redirection_argument(current_type, command, \
		split_command + 1) == SUCCESS)
	{
		if (current_type == REDIRECTION_DINPUT)
		{
			if (parse_delimiter(command, split_command + 1) == SUCCESS)
				ret = SUCCESS;
		}
		else
		{
			if (open_redirection_file(command, \
				*(split_command + 1), current_type) == SUCCESS)
				ret = SUCCESS;
		}
		free_redirection(current_type, split_command);
		command->argc -= 2;
	}
	return (ret);
}
