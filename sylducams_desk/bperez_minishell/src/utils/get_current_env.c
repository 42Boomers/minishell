/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_current_env.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngeschwi <nathan.geschwind@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 14:57:24 by ngeschwi          #+#    #+#             */
/*   Updated: 2021/11/25 14:43:56 by ngeschwi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_current_env_int(t_shell *shell, char *str)
{
	int		index;
	char	**tab;

	index = 0;
	while (shell->env[index])
	{
		tab = ft_split(shell->env[index], '=');
		if (!ft_strcmp(tab[0], str))
		{
			free_tab(tab);
			return (index);
		}
		free_tab(tab);
		index++;
	}
	return (-1);
}

char	*get_current_env(t_shell *shell, char *str)
{
	int		index;
	int		index_equal;
	char	**array;

	index = 0;
	if (*str)
	{
		while (shell->env[index])
		{
			array = ft_split(shell->env[index], '=');
			if (!array && ft_tablen(array) != 2)
				break ;
			index_equal = ft_strclen(shell->env[index], '=');
			if (!ft_strcmp(array[0], str))
			{
				ft_free_2d((void **)array, ft_tablen(array));
				return (shell->env[index] + index_equal + 1);
			}
			index++;
		}
		ft_free_2d((void **)array, ft_tablen(array));
	}
	return ("");
}
