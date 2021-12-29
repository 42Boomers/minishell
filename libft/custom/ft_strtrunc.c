/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrunc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblache <jblache@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 01:30:38 by jblache           #+#    #+#             */
/*   Updated: 2021/12/29 18:34:47 by jblache          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "custom.h"

static char	**ft_strtrunc_2(char *str, int i, char **out)
{
	int			j;

	out[1] = malloc(sizeof(char) * (ft_strlen(str) - i));
	if (!out[1])
	{
		free(out[0]);
		free(out);
		return (NULL);
	}
	j = i;
	while (str[++j])
		out[1][j - i - 1] = str[j];
	out[1][j - i - 1] = 0;
	out[0][i] = 0;
	while (--i >= 0)
		out[0][i] = str[i];
	return (out);
}

/**
 * @brief Cut a string in two parts.
 * Seperator is the first char c.
 */
char	**ft_strtrunc(char *str, char c)
{
	int			i;
	char		**out;

	i = 0;
	out = malloc(sizeof(char *) * 2);
	if (!out)
		return (NULL);
	while (str[i] && str[i] != c)
		i++;
	if (!str[i])
	{
		free(out);
		return (NULL);
	}
	out[0] = malloc(sizeof(char) * (i + 1));
	if (!out[0])
	{
		free(out);
		return (NULL);
	}
	return (ft_strtrunc_2(str, i, out));
}
