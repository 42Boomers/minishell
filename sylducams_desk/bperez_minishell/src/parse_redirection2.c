/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirection2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngeschwi <nathan.geschwind@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 05:22:24 by bperez            #+#    #+#             */
/*   Updated: 2021/11/25 17:57:20 by bperez           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_redirection_file(t_command *command, char *arg, int type)
{
	struct stat	sct_stat;

	if (type == REDIRECTION_INPUT)
		command->fd_in = open(arg, O_RDWR);
	else if (type == REDIRECTION_DOUTPUT)
		command->fd_out = open(arg, O_CREAT | O_RDWR | O_APPEND, S_IRWXU);
	else if (type == REDIRECTION_OUTPUT)
	{
		stat(arg, &sct_stat);
		if (sct_stat.st_atime != 0)
			unlink(arg);
		command->fd_out = open(arg, O_CREAT | O_RDWR, S_IRWXU);
	}
	if (command->fd_in == -1)
	{
		command->shell->parsing_error = 1;
		return (ft_error("Error no such file or directory", ERROR));
	}
	return (SUCCESS);
}

int	add_delimiter_to_list(t_command *command, char **split_command)
{
	int		len;
	char	**delimiters;
	int		i;

	len = ft_tablen(command->delimiters);
	delimiters = malloc(sizeof(char *) * (len + 2));
	if (delimiters)
	{
		i = 0;
		while (command->delimiters[i])
		{
			delimiters[i] = command->delimiters[i];
			i++;
		}
		free(command->delimiters);
		delimiters[i] = *split_command;
		delimiters[i + 1] = NULL;
		command->delimiters = delimiters;
		return (SUCCESS);
	}
	return (ERROR);
}

int	add_delimiters_to_redirection(char **command, int *i)
{
	if (*i > 0 && (*command)[*i - 1] != SPLIT_DELIMITER)
	{
		*command = ft_tmp(*command, add_char(*command, *i, SPLIT_DELIMITER));
		if (*command == NULL)
			return (ERROR);
		*i += 1;
	}
	if ((*command)[*i + 1] == '<' || (*command)[*i + 1] == '>')
	{
		if (((*command)[*i] == '<' && (*command)[*i + 1] == '>') || \
			((*command)[*i] == '>' && (*command)[*i + 1] == '<'))
			return (ERROR);
		*i += 1;
	}
	if ((*command)[*i + 1] != '\0' && (*command)[*i + 1] != ' ')
	{
		*command = ft_tmp(*command, \
					add_char(*command, *i + 1, SPLIT_DELIMITER));
		if (command == NULL)
			return (ERROR);
		*i += 1;
	}
	return (SUCCESS);
}

int	parse_delimiter(t_command *command, char **split_command)
{
	char	**delimiters;

	if (command->delimiters)
	{
		if (add_delimiter_to_list(command, split_command) == SUCCESS)
			return (SUCCESS);
	}
	else
	{
		delimiters = malloc(sizeof(char *) * 2);
		if (delimiters)
		{
			delimiters[0] = *split_command;
			delimiters[1] = NULL;
			command->delimiters = delimiters;
			return (SUCCESS);
		}
	}
	return (ERROR);
}
