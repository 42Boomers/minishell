/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stradd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlepart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 16:14:44 by rlepart           #+#    #+#             */
/*   Updated: 2021/01/10 15:48:51 by rlepart          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_stradd_back(char **str, char *line)
{
	int		i;
	char	**dup;

	i = 0;
	while (str && str[i])
		i++;
	if (!(dup = ft_calloc(i + 2, sizeof(*dup))))
		return (NULL);
	i = 0;
	while (str && str[i])
	{
		dup[i] = str[i];
		i++;
	}
	dup[i] = line;
	dup[i + 1] = NULL;
	if (str)
		free(str);
	return (dup);
}
