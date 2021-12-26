/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tglory <tglory@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 19:53:38 by tglory            #+#    #+#             */
/*   Updated: 2021/12/24 19:54:35 by tglory           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_print_cmd_not_found(char *name, char *cmd)
{
	if (errno == ENOENT)
	{
		ft_putstr_fd(name, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putendl_fd(": command not found", 2);
	}
	else
		ms_print_error(name, cmd);
	exit(127);
}

t_list	*lst_cpy(t_list *lst)
{
	t_list	*cpy;

	cpy = malloc(sizeof(*cpy));
	memcpy(cpy, lst, sizeof(*lst));
	return (cpy);
}

void	ms_fork_free(int fd_in, int pip_end0, int pip_end1)
{
	close(fd_in);
	close(pip_end0);
	close(pip_end1);
}
