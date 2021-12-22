/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlepart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 16:21:28 by rlepart           #+#    #+#             */
/*   Updated: 2021/01/16 16:21:29 by rlepart          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;
	char	*str;

	i = 0;
	str = (char *)haystack;
	if (needle[0] == '\0')
		return (str);
	while (i < len && str[i])
	{
		if (str[i] == needle[0])
		{
			j = 0;
			while (i + j < len && needle[j] == str[i + j] && needle[j] != '\0')
				j++;
			if (needle[j] == '\0' && i + j < len + 1)
				return (str + i);
		}
		i++;
	}
	return (0);
}
