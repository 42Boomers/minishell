/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_prompt_tonorm.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngeschwi <nathan.geschwind@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 23:00:13 by bperez            #+#    #+#             */
/*   Updated: 2021/11/25 16:49:22 by bperez           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command	*goto_first_command(t_command *current)
{
	if (current)
		while (current->prev)
			current = current->prev;
	return (current);
}

void	check_quotes(char c, int *quote, int *double_quote)
{
	if (c == '"' && *quote == 0)
	{
		if (*double_quote == 0)
			*double_quote = 1;
		else
			*double_quote = 0;
	}	
	else if (c == '\'' && *double_quote == 0)
	{
		if (*quote == 0)
			*quote = 1;
		else
			*quote = 0;
	}
}

char	*remove_char(char *str, int i)
{
	char	*new_str;
	int		new_length;
	int		j;

	new_length = ft_strlen(str) - 1;
	new_str = malloc(sizeof(char) * (new_length + 1));
	if (new_str)
	{
		j = new_length + 1;
		new_str[new_length] = '\0';
		while (new_length--)
		{
			j--;
			if (j == i)
				j--;
			new_str[new_length] = str[j];
		}
	}
	return (new_str);
}

int	interpret_quotes(char **split_command, int *i, int *quote, int *dq)
{
	check_quotes((*split_command)[*i], quote, dq);
	if (((*split_command)[*i] == '"' && *quote == 0) || \
		((*split_command)[*i] == '\'' && *dq == 0))
	{
		*split_command = ft_tmp(*split_command, \
							remove_char(*split_command, *i));
		if (*split_command == NULL)
			return (ERROR);
	}
	else if (((*split_command)[*i] == '"' && *quote == 1) || \
		((*split_command)[*i] == '\'' && *dq == 1))
		*i += 1;
	return (SUCCESS);
}
