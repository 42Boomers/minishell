/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrozniec <mrozniec@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 17:34:55 by mrozniec          #+#    #+#             */
/*   Updated: 2021/12/29 17:36:09 by mrozniec         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_heredoc_error(char ***line)
{
	write(1, "> ", 2);
	*line = NULL;
	*line = malloc(sizeof(char *) * 2);
	(*line)[1] = NULL;
	(*line)[0] = NULL;
	if (get_next_line(0, (*line)) == 0)
	{
		free((*line)[0]);
		(*line)[0] = NULL;
	}
	if (!(*line) || !(*line)[0])
	{
		if (*line)
			free(*line);
		unlink(".ms_heredoc");
		return (-2);
	}
	return (0);
}

void	ms_red_init_wh(int *redir, int f_red)
{
	if (f_red == (f_red | 4) && redir[0] > 0)
		close(redir[0]);
	if (f_red == (f_red | 2) && redir[1] > 0)
		close(redir[1]);
}

void	ft_red_init_val(int *redir, int *f_red)
{
	redir[0] = -5;
	redir[1] = -5;
	*f_red = 1;
}
