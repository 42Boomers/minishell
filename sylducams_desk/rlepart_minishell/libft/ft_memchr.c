/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlepart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 16:19:32 by rlepart           #+#    #+#             */
/*   Updated: 2021/01/16 16:19:33 by rlepart          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*str;
	unsigned char		ch;
	size_t				i;

	ch = c;
	str = s;
	i = 0;
	while (i < n)
	{
		if (str[i] == ch)
		{
			return ((void *)(s + i));
		}
		i++;
	}
	return (0);
}
