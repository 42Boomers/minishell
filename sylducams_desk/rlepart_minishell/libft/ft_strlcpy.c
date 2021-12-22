/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlepart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 16:21:12 by rlepart           #+#    #+#             */
/*   Updated: 2021/01/16 16:21:13 by rlepart          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	if (!dst || !src)
		return (0);
	i = 0;
	if (src[0] == '\0')
		dst[0] = '\0';
	while (src[i])
	{
		if (size != 0 && i < size - 1)
			dst[i] = src[i];
		i++;
		if (i == size - 1)
		{
			dst[i] = '\0';
		}
	}
	if (i < size)
		dst[i] = '\0';
	return (i);
}
