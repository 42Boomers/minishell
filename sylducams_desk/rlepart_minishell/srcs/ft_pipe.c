/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-kada <mel-kada@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 15:26:59 by mel-kada          #+#    #+#             */
/*   Updated: 2021/03/11 20:40:19 by mel-kada         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		ft_check_redir(char *str, int i)
{
	char	**k;

	while (str[++i])
		if ((str[i] == '>' || str[i] == '<') && !ft_is_ignored(str, str[i], i))
		{
			i = i + (str[i + 1] == '>');
			k = ft_split_spaces2(&(str[++i]));
			if (!k)
			{
				ft_throw_error("syntax error near unexpected token `newline'");
				free(str);
				return (0);
			}
			if (k[0][0] == '<' || k[0][0] == '>')
			{
				ft_throw_error("syntax error near unexpected token '>' or '<'");
				free(str);
				ft_free_tab(k);
				return (0);
			}
			ft_free_tab(k);
		}
	return (1);
}

int		ft_check_pipe(char *str)
{
	int		i;
	char	**k;

	i = -1;
	k = NULL;
	while (str[++i])
	{
		if ((str[i] == '|') && !ft_is_ignored(str, str[i], i))
		{
			k = ft_split_spaces2(&(str[++i]));
			if (!k)
			{
				ft_throw_error("syntax error near unexpected token `newline'");
				free(str);
				return (0);
			}
			if (k[0][0] == '|')
			{
				ft_throw_error("syntax error near unexpected token `|'");
				free(str);
				return (0);
			}
		}
	}
	return (1);
}

void	ft_close(int *fd, int *fd_old, int *i)
{
	wait(NULL);
	close(fd[1]);
	*fd_old = fd[0];
	(*i)++;
}

void	ft_process(t_content *content, char **list)
{
	int fd[3];
	int pid;
	int	i;

	i = 0;
	fd[2] = 0;
	while (list[i])
	{
		pipe(fd);
		pid = fork();
		if (pid == 0)
		{
			ft_pipe_move(&fd[2], list, fd, i);
			if (ft_redir_parse(content, &(list[i])) != -1)
				ft_pars(content,
						ft_split_spaces(ft_get_var(content, list[i])), 1);
			exit(1);
		}
		else
		{
			ft_close(fd, &fd[2], &i);
			waitpid(pid, fd, 0);
			kill(pid, SIGTERM);
		}
	}
}

int		ft_check_quotes(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
		i++;
	if (!(ft_no_d_quote(str, i) && ft_no_s_quote(str, i)))
	{
		ft_throw_error("Quote not closed.");
		free(str);
		return (0);
	}
	return (1);
}
