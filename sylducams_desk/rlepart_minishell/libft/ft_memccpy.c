/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlepart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 16:19:26 by rlepart           #+#    #+#             */
/*   Updated: 2021/01/16 16:19:29 by rlepart          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char		ch;
	size_t				i;
	unsigned char		*str1;
	const unsigned char	*str2;

	str1 = dst;
	str2 = src;
	i = 0;
	ch = c;
	while (i < n)
	{
		*(str1 + i) = *(str2 + i);
		if (*(str1 + i) == ch)
		{
			return (dst + i + 1);
		}
		i++;
	}
	return (0);
}
