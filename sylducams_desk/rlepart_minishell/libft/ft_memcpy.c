/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlepart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 16:19:48 by rlepart           #+#    #+#             */
/*   Updated: 2021/01/16 16:19:49 by rlepart          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t		i;
	char		*str1;
	const char	*str2;

	if (!dst && !src)
		return (0);
	str1 = dst;
	str2 = src;
	i = 0;
	while (i < n)
	{
		*(str1 + i) = *(str2 + i);
		i++;
	}
	return (dst);
}
