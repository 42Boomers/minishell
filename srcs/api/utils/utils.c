/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tglory <tglory@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 19:53:38 by tglory            #+#    #+#             */
/*   Updated: 2021/12/28 02:22:42 by tglory           ###   ########lyon.fr   */
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

t_list	*ms_env_lst_cpy(t_list *lst)
{
	t_list	*cpy;

	cpy = NULL;
	while (lst)
	{
		ft_lstadd_back(&cpy, ft_lstnew(lst->content));
		lst = lst->next;
	}
	return (cpy);
}

void	ms_fork_free(int fd_in, int pip_end0, int pip_end1)
{
	if (fd_in > -1)
		close(fd_in);
	close(pip_end0);
	close(pip_end1);
}

char	*ft_init_fillstr(int m[4], int n)
{
	m[1] = 0;
	m[0] = n;
	m[3] = 0;
	return (ft_strdup("\0"));
}
