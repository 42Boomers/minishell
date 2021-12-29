/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrozniec <mrozniec@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 13:51:11 by mrozniec          #+#    #+#             */
/*   Updated: 2021/12/21 15:15:29 by mrozniec         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	ms_history_read(t_master *master)
{
	char	*line;
	int		fd;
	int		ret;

	fd = open(master->hist_file, O_RDONLY | O_CREAT,
			S_IRWXU | S_IRGRP | S_IROTH);
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
		add_history(line);
		free(line);
	}
	close(fd);
	return (TRUE);
}

t_bool	ms_history_write(t_master *master, char *command)
{
	int		fd;

	fd = open(master->hist_file, O_WRONLY | O_CREAT | O_APPEND,
			S_IRWXU | S_IRGRP | S_IROTH);
	if (fd == -1)
		return (FALSE);
	ft_putstr_fd(command, fd);
	ft_putstr_fd("\n", fd);
	close(fd);
	return (TRUE);
}
