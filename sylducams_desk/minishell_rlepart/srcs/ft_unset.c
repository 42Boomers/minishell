/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlepart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 15:43:15 by rlepart           #+#    #+#             */
/*   Updated: 2021/02/19 17:34:15 by rlepart          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		ft_da_cmp(char **tab, char *cmp)
{
	return ((ft_strncmp(cmp, *tab, ft_strlen(*tab)) == 0) &&
			((size_t)ft_strichr(cmp, '=') == ft_strlen(*tab)
			|| ((ft_strichr(cmp, '=') == -1) &&
				(!ft_strcmp(*tab, cmp)))));
}

void	ft_unset(t_content *content, char **tab, int pipe)
{
	int		i;

	while (*tab && !pipe)
	{
		i = 0;
		if (ft_strichr(*tab, '=') != -1)
		{
			ft_putstr_fd("minishell: unset: `", 1);
			ft_putstr_fd(*tab, 1);
			ft_putstr_fd("': not a valid identifier\n", 1);
			errno = 1;
		}
		else
			while (content->envp[i])
			{
				if (ft_da_cmp(tab, content->envp[i]))
				{
					content->envp = ft_str_remove(content->envp, i);
					break ;
				}
				i++;
			}
		tab++;
	}
}
