/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblache <jblache@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 17:54:51 by jblache           #+#    #+#             */
/*   Updated: 2021/12/29 18:34:47 by jblache          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f) (unsigned int, char))
{
	unsigned int	i;
	char			*dst;

	if (!(!s || !f))
	{
		i = ft_strlen((char *)s);
		dst = malloc(sizeof(*s) * ((i + 1)));
		if (!dst)
			return (dst);
		i = 0;
		while (s[i])
		{
			dst[i] = f(i, s[i]);
			i++;
		}
		dst[i] = 0;
		return (dst);
	}
	return (NULL);
}
