/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tglory <tglory@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 13:51:11 by tglory            #+#    #+#             */
/*   Updated: 2021/12/08 19:43:05 by tglory           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	mv_history_read(t_master *master)
{
	char	*line;
	int		fd;
	int		ret;

	fd = open(master->hist_file, O_RDONLY);
	if (fd == -1)
		return (FALSE);
	ret = 1;
	line = NULL;
	while (ret > 0)
	{
		ret = get_next_line(fd, &line);
		if (!line)
			break ;
		if (ft_isblank(line))
		{
			free(line);
			continue ;
		}
		// if (master->verbose)
		// 	printf("ADDED TO HISTORY: %s\n", line);
		add_history(line);
		free(line);
		// ms_garbage_master_add(master, &line, free);
	}
	close(fd);
	return (TRUE);
}

t_bool	mv_history_write(t_master *master, char *command)
{
	int		fd;

	fd = open(master->hist_file, O_WRONLY | O_CREAT | O_APPEND, 644);
	if (fd == -1)
		return (FALSE);
	ft_putstr_fd(command, fd);
	ft_putstr_fd("\n", fd);
	close(fd);
	return (TRUE);
}
