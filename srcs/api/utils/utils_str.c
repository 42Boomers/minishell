/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tglory <tglory@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 03:50:38 by tglory            #+#    #+#             */
/*   Updated: 2021/12/24 17:03:01 by tglory           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	ft_strisfullof(char *str, char c)
{
	if (!str)
		return (FALSE);
	while (*str && *str == c)
		str++;
	if (!str)
		return (TRUE);
	return (FALSE);
}

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

	while (lst)
	{
		ft_lstadd_back(&cpy, ft_lstnew(lst->content));
		lst = lst->next;
	}
	return (cpy);
}
