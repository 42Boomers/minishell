/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_prompt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: neben <neben@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 23:00:13 by bperez            #+#    #+#             */
/*   Updated: 2021/11/29 14:02:06 by bperez           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_program_path(t_shell *shell, t_command *command)
{
	int		i;
	char	*path;

	i = 0;
	while (command->argv[0][i])
	{
		if (command->argv[0][i] == '/')
			return (ft_strdup(command->argv[0]));
		i++;
	}
	i = 0;
	while (shell->all_path[i])
	{
		path = ft_strjoin(shell->all_path[i], "/");
		path = ft_strjoin(path, command->argv[0]);
		if (access(path, X_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	shell->parsing_error = 1;
	return (NULL);
}

int	is_program_builtin(char *program)
{
	if (!program)
		return (1);
	if (!ft_strcmp(program, "cd"))
		return (1);
	if (!ft_strcmp(program, "export"))
		return (1);
	if (!ft_strcmp(program, "unset"))
		return (1);
	if (!ft_strcmp(program, "echo"))
		return (1);
	if (!ft_strcmp(program, "pwd"))
		return (1);
	if (!ft_strcmp(program, "env"))
		return (1);
	if (!ft_strcmp(program, "exit"))
		return (1);
	return (0);
}

int	parse_command(t_shell *shell, t_command *current_command, char **command)
{
	char	**ret;

	if (split_command(command) == SUCCESS)
	{
		ret = ft_split(*command, SPLIT_DELIMITER);
		if (ret && ret[0])
		{
			current_command->shell = shell;
			current_command->argc = ft_strlen_2d(ret);
			if (parse_argv(current_command, ret) == SUCCESS)
			{
				current_command->argv = ret;
				if (!is_program_builtin(current_command->argv[0]))
				{
					current_command->program_path = get_program_path(shell, \
													current_command);
					if (current_command->program_path == NULL)
						return (ft_error("Error, command not found", ERROR));
				}
				return (SUCCESS);
			}
		}
		ft_free_2d((void **)ret, current_command->argc);
	}
	return (ERROR);
}

int	add_command(t_shell *shell, char *command)
{
	t_command	*current_command;

	current_command = malloc(sizeof(t_command));
	if (current_command)
	{
		ft_bzero(current_command, sizeof(t_command));
		if (shell->command_list != NULL)
		{
			current_command->prev = shell->command_list;
			current_command->prev->next = current_command;
		}
		shell->command_list = current_command;
		if (parse_command(shell, current_command, &command) == SUCCESS)
		{
			free(command);
			return (SUCCESS);
		}
	}
	free(command);
	return (ERROR);
}

int	parse_prompt(t_shell *shell, char *prompt)
{
	int	i;
	int	q;
	int	dq;
	int	prompt_length;

	if (prompt)
	{
		i = 0;
		q = 0;
		dq = 0;
		prompt_length = ft_strlen(prompt);
		while (prompt_length-- >= 0)
		{
			check_quotes(prompt[i], &q, &dq);
			if (prompt[i] == '\0' || (prompt[i] == '|' && q == 0 && dq == 0))
			{
				if (add_command(shell, ft_substr(prompt, 0, i)) == ERROR)
					return (ERROR);
				prompt += i + 1;
				i = -1;
			}
			i++;
		}
	}
	return (SUCCESS);
}
