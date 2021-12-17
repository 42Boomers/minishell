/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_spaces.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-kada <mel-kada@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 15:55:39 by rlepart           #+#    #+#             */
/*   Updated: 2021/03/03 21:32:05 by mel-kada         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

/*
** \   0 0 1 1
**' dq 0 1 0 1
**0	 1 0 0 0
**1	 1 0 0 0
**\///"   0 1 0 1
**1	 1 1 0 0
**\//\	 0 1 0 1
**1	 1 1 0 0
*/

#include "../includes/minishell.h"

char	**ft_split_spaces(char *str)
{
	char	*save;
	char	**tab;
	int		i;

	save = str;
	tab = NULL;
	while (str && *str)
	{
		i = 0;
		str = ft_skip_spaces(str);
		while (str[i] && !(ft_isspace(str[i]) && ft_no_bs(str, i) &&
					ft_no_s_quote(str, i) && ft_no_d_quote(str, i)))
			i++;
		if (i)
			tab = ft_stradd_back(tab, ft_remove_bs_q(ft_substr(str, 0, i)));
		str += i;
	}
	if (save)
		free(save);
	return (tab);
}

char	**ft_split_spaces2(char *str)
{
	char	**tab;
	int		i;

	tab = NULL;
	while (str && *str)
	{
		i = 0;
		if (*str == '<' || *str == '>')
			str++;
		str = ft_skip_spaces(str);
		while (str[i] && !(
					(ft_isspace(str[i]) || str[i] == '<' || str[i] == '>')
					&& ft_no_bs(str, i) &&
					ft_no_s_quote(str, i) && ft_no_d_quote(str, i)))
			i++;
		if (i)
			tab = ft_stradd_back(tab, ft_substr(str, 0, i));
		str += i;
	}
	return (tab);
}

/*
**char	**ft_split_spaces(char *str)
**{
**	char	*save;
**	char	**tab;
**	int		i;
**	int		j;
**
**	save = str;
**	tab = NULL;
**	while (str && *str)
**	{
**		i = 0;
**		j = 0;
**		str = ft_skip_spaces(str);
**		while (str[i] && (!ft_isspace(str[i]) || !ft_no_bs(str, i)))
**		{
**			if ((j = ((str[i] == '\'') + 2 * (str[i] == '\"')) *
**						ft_no_bs(str, i)))
**			{
**				if (i)
**					ft_memmove(str + 1, str, i);
**				i = -1;
**				str++;
**			}
**			while (str[++i] && j)
**				if (ft_no_bs(str, i) && ((j == 2 && str[i] == '\"') ||
**							(j == 1 && str[i] == '\'')))
**				{
**					while (str[i + 1] && !ft_isspace(str[i + 1]))
**					{
**						str[i] = str[i + 1];
**						i++;
**					}
**					if (i > 0)
**						tab = ft_stradd_back(tab, ft_substr(str, 0, i));
**					str = str + i + 1;
**					i = -1;
**					j = 0;
**					str = ft_skip_spaces(str);
**				}
**		}
**		if (i)
**			tab = ft_stradd_back(tab, ft_substr(str, 0, i));
**		str = str + i;
**	}
**	free(save);
**	return (tab);
**}
*/
