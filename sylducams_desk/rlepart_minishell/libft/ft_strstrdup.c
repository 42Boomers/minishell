/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstrdup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlepart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 16:23:15 by rlepart           #+#    #+#             */
/*   Updated: 2021/01/18 16:08:37 by rlepart          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	**ft_strstrdup(char **str)
{
	char	**dup;
	int		i;

	i = 0;
	while (str && str[i])
		i++;
	if (!(dup = malloc((i + 1) * sizeof(*dup))))
		return (NULL);
	i = 0;
	while (str && str[i])
	{
		if (!(dup[i] = ft_strdup(str[i])))
		{
			ft_free_tab((void *)str);
			return (NULL);
		}
		i++;
	}
	dup[i] = NULL;
	return (dup);
}
