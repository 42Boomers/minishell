/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tools2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-kada <mel-kada@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 15:27:11 by mel-kada          #+#    #+#             */
/*   Updated: 2021/03/11 20:43:41 by mel-kada         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		ft_is_ignored(char const *str, char c, int index)
{
	int		i;
	int		is_single_quotes;
	int		is_double_quotes;
	int		is_backslash;

	i = -1;
	is_single_quotes = 0;
	is_double_quotes = 0;
	is_backslash = 0;
	while (str[++i])
	{
		if (i == index && str[i] == c && !is_backslash &&
			!is_double_quotes && !is_single_quotes)
			return (0);
		if (str[i] == '\\' && !is_double_quotes && !is_single_quotes)
			is_backslash = !is_backslash;
		if (str[i] == '\'' && !is_backslash && c != '\'')
			is_single_quotes = !is_single_quotes;
		if (str[i] == '\"' && !is_backslash && c != '\"')
			is_double_quotes = !is_double_quotes;
		if (is_backslash && str[i] != '\\')
			is_backslash = 0;
	}
	return (1);
}

void	ft_throw_error(char *msg)
{
	ft_putstr_fd("minishell -> ", 1);
	ft_putstr_fd(msg, 1);
	ft_putchar_fd('\n', 1);
}

void	ft_pipe_move(int *old_fd, char **str, int *fd, int index)
{
	dup2(*old_fd, 0);
	if (str[index + 1])
		dup2(fd[1], 1);
	else
		dup2(1, 1);
	close(fd[0]);
}

void	ft_restore_fd(void)
{
	if (g_saved_fd[0] != -1 && g_saved_fd[1] != -1)
	{
		dup2(g_saved_fd[1], g_saved_fd[0]);
		g_saved_fd[0] = -1;
		g_saved_fd[1] = -1;
	}
}

void	ft_memfree(char **str)
{
	int i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	if (str)
	{
		free(str);
		str = NULL;
	}
}
