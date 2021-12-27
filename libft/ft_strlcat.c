/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tglory <tglory@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 17:54:31 by tglory            #+#    #+#             */
/*   Updated: 2021/12/07 09:03:05 by tglory           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dst_len;
	size_t	src_len;
	size_t	i;

	dst_len = ft_strlen(dst);
	if (dst_len > size)
		dst_len = size;
	src_len = ft_strlen(src);
	if (dst_len < size)
	{
		i = -1;
		while (dst_len + ++i < size && i < src_len)
			dst[dst_len + i] = src[i];
		if (dst_len + i < size)
			dst[dst_len + i] = 0;
		else
			dst[size - 1] = 0;
	}
	return (dst_len + src_len);
}
