/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlepart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 15:36:13 by rlepart           #+#    #+#             */
/*   Updated: 2021/02/20 11:56:02 by rlepart          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_get_export_buf(t_content *content, char **tab)
{
	int		i;
	int		index;

	i = 0;
	while (tab[i] != NULL)
	{
		if (tab[i][0] != '_' || tab[i][1] != '=' ||
				(content->index_cmd == 0))
		{
			content->buf = ft_join_free(content->buf, "declare -x ", 2);
			index = ft_strichr(tab[i], '=');
			if (index == -1)
				content->buf = ft_join_free(content->buf, tab[i], 2);
			else
			{
				content->buf = ft_join_free(ft_join_free(content->buf,
							ft_substr(tab[i], 0, index + 1), 3), "\"", 2);
				content->buf = ft_join_free(ft_join_free(content->buf,
							ft_strdup(tab[i] + index + 1), 3), "\"", 2);
			}
			content->buf = ft_join_free(content->buf, "\n", 2);
		}
		i++;
	}
}

void	ft_order_export(t_content *content, char **tab)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (tab && tab[i] && tab[i + 1])
	{
		j = i + 1;
		while (tab[j])
		{
			if (ft_strcmp(tab[i], tab[j]) > 0)
			{
				tmp = tab[i];
				tab[i] = tab[j];
				tab[j] = tmp;
			}
			j++;
		}
		i++;
	}
	ft_get_export_buf(content, tab);
}

void	ft_print_export(t_content *content, int pipe)
{
	char	**tab;

	tab = ft_strstrdup(content->envp);
	if (tab)
	{
		ft_order_export(content, tab);
		if (!pipe)
		{
			ft_putstr_fd(content->buf, 1);
			free(content->buf);
			content->buf = NULL;
			ft_free_tab(tab);
		}
	}
}

void	ft_export(t_content *content, char **tab, int pipe)
{
	char	*str;
	int		index;

	if (tab && *tab)
		while (!pipe && tab && *tab)
		{
			index = ft_strichr(*tab, '=');
			if (index != -1)
			{
				str = ft_substr(*tab, 0, index);
				ft_edit_env(content, str, ft_strdup(*tab));
				free(str);
			}
			else
			{
				if (!ft_get_env(content, *tab))
					content->envp = ft_stradd_back(content->envp,
							ft_strdup(*tab));
			}
			tab++;
		}
	else
		ft_print_export(content, pipe);
}

void	ft_edit_underscore(t_content *content, char **str, int pipe)
{
	int	i;

	i = 0;
	if (!pipe)
	{
		content->index_cmd++;
		while (str && str[i])
			i++;
		if (str && i > 0)
			ft_edit_env(content, "_", ft_strjoin("_=", str[i - 1]));
	}
	ft_free_tab(str);
}
