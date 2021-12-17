/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlepart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 16:19:51 by rlepart           #+#    #+#             */
/*   Updated: 2021/01/16 16:19:56 by rlepart          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t				i;
	char				*str2;

	if (!dst && !src)
		return (0);
	str2 = dst;
	i = 0;
	if (src > dst)
	{
		while (i < len)
		{
			str2[i] = ((const char *)(src))[i];
			i++;
		}
	}
	else
	{
		while (i < len)
		{
			str2[len - i - 1] = ((const char *)(src))[len - i - 1];
			i++;
		}
	}
	return (dst);
}
