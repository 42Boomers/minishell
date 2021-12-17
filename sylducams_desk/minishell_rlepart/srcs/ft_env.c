/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlepart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 15:48:37 by rlepart           #+#    #+#             */
/*   Updated: 2021/02/19 16:02:00 by rlepart          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_edit_env(t_content *content, char *name, char *value)
{
	char	**tab;
	int		found;

	tab = content->envp;
	found = 0;
	while (tab && *tab)
	{
		if (ft_strncmp(*tab, name, ft_strlen(name)) == 0 &&
				((*tab)[ft_strlen(name)] == '=' ||
				(*tab)[ft_strlen(name)] == '\0'))
		{
			found = 1;
			free(*tab);
			*tab = value;
			break ;
		}
		else
			tab++;
	}
	if (!found)
		content->envp = ft_stradd_back(content->envp, value);
}

char	*ft_get_env(t_content *content, char *name)
{
	char	**str;
	int		i;

	i = 0;
	str = content->envp;
	while (str && str[i])
	{
		if ((ft_strncmp(str[i], name, ft_strlen(name)) == 0) &&
				(size_t)ft_strichr(str[i], '=') == ft_strlen(name))
			return (str[i] + ft_strlen(name) + 1);
		i++;
	}
	return (NULL);
}
