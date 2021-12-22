/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_insert.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlepart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 18:48:35 by rlepart           #+#    #+#             */
/*   Updated: 2021/02/06 12:29:09 by rlepart          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	*ft_insert(char *src, int index, char *word)
{
	char	*str;
	int		i[2];

	if (!src || !word)
		return (src);
	if ((index < 0) || ((size_t)index > ft_strlen(src)) || !(str =
				malloc(sizeof(*str) * (ft_strlen(word) + ft_strlen(src) + 1))))
		return (NULL);
	i[0] = -1;
	i[1] = 0;
	while (++(i[0]) < index)
		str[i[0]] = src[i[0]];
	while (word[i[1]])
	{
		str[i[0] + i[1]] = word[i[1]];
		i[1]++;
	}
	while (src[i[0]])
	{
		str[i[0] + i[1]] = src[i[0]];
		i[0]++;
	}
	str[i[0] + i[1]] = '\0';
	free(src);
	return (str);
}
