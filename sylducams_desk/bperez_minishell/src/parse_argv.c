/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_argv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperez <bperez@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 05:14:50 by bperez            #+#    #+#             */
/*   Updated: 2021/11/25 16:48:49 by bperez           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	expand_variables(t_command *cmd, char **split_cmd, int *i)
{
	if ((*split_cmd)[*i] == '$' && (*split_cmd)[*i + 1] == '?')
	{
		if (expand_exit_status_variable(cmd, split_cmd, *i) == ERROR)
			return (ERROR);
	}
	else if ((*split_cmd)[*i] == '$' && ft_isalnum((*split_cmd)[*i + 1]))
	{
		if (expand_env_variable(cmd, split_cmd, *i + 1) == ERROR)
			return (ERROR);
		*i -= 1;
	}
	return (SUCCESS);
}

int	interpret_the_rest(t_command *cmd, char **split_cmd, int *i, int dq)
{
	if ((*split_cmd)[*i] == '$')
	{
		if (expand_variables(cmd, split_cmd, i) == ERROR)
			return (ERROR);
	}
	else if ((*split_cmd)[*i] == '~' && dq == 0)
	{
		if (*i == 0 && ((*split_cmd)[*i + 1] == '\0' || \
			(*split_cmd)[*i + 1] == '/'))
		{
			if (expand_tilde(cmd, split_cmd, *i) == ERROR)
				return (ERROR);
		}
	}
	else if (((*split_cmd)[*i] == '<' || (*split_cmd)[*i] == '>') && dq == 0)
	{
		if (parse_redirection(cmd, split_cmd) == ERROR)
			return (ERROR);
		*i = -1;
	}
	return (SUCCESS);
}

int	parse_argv(t_command *current_command, char **split_command)
{
	int	i;
	int	quote;
	int	double_quote;

	quote = 0;
	double_quote = 0;
	while (*split_command)
	{
		i = 0;
		while (*split_command && (*split_command)[i])
		{
			if (interpret_quotes(split_command, &i, &quote, &double_quote))
				return (ERROR);
			if ((*split_command)[i] && (*split_command)[i] != '"' && \
				(*split_command)[i] != '\'')
			{
				if (quote == 0 && interpret_the_rest(current_command, \
						split_command, &i, double_quote) == ERROR)
					return (ERROR);
				i++;
			}
		}
		split_command++;
	}
	return (SUCCESS);
}

char	*add_char(char *str, int index, char c)
{
	char	*new_str;
	int		new_len;
	int		i;

	new_len = ft_strlen(str);
	new_str = malloc(sizeof(char) * (new_len + 1 + 1));
	if (new_str)
	{
		i = 0;
		while (*str)
		{
			if (i == index)
				new_str[i] = c;
			else
			{
				new_str[i] = *str;
				str++;
			}
			i++;
		}
		new_str[i] = '\0';
	}
	return (new_str);
}

int	split_command(char **command)
{
	int		i;
	int		quote;
	int		double_quote;

	i = 0;
	quote = 0;
	double_quote = 0;
	while ((*command)[i])
	{
		check_quotes((*command)[i], &quote, &double_quote);
		if ((*command)[i] == ' ' && quote == 0 && double_quote == 0)
			(*command)[i] = SPLIT_DELIMITER;
		else if (((*command)[i] == '<' || (*command)[i] == '>') && \
					quote == 0 && double_quote == 0)
		{
			if (add_delimiters_to_redirection(command, &i) == ERROR)
				return (ERROR);
		}
		i++;
	}
	return (SUCCESS);
}
