/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngeschwi <nathan.geschwind@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 14:11:14 by ngeschwi          #+#    #+#             */
/*   Updated: 2021/11/29 13:17:33 by bperez           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_error_fork(t_shell *shell, char *str)
{
	(void)shell;
	perror(str);
	if (errno == 13)
		exit(126);
	if (errno == 14)
		exit(127);
	exit(128 + errno);
}

int	ft_error(char *str, int wich_one)
{
	perror(str);
	return (wich_one);
}

void	ft_error2(char *str)
{
	perror(str);
}

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}
