/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlepart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 16:21:08 by rlepart           #+#    #+#             */
/*   Updated: 2021/01/16 16:21:10 by rlepart          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (dst[i] && i < size)
		i++;
	j = 0;
	while (j + i + 1 < size && src[j] != '\0')
	{
		dst[i + j] = src[j];
		j++;
	}
	if (i + j < size)
		dst[i + j] = '\0';
	while (src[j])
		j++;
	return (i + j);
}
