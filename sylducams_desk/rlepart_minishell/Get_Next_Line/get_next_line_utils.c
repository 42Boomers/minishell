/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlepart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 17:44:30 by rlepart           #+#    #+#             */
/*   Updated: 2021/02/06 17:28:53 by rlepart          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	i;
	size_t	j;

	if (!s)
		return (NULL);
	j = 0;
	while (s[j])
		j++;
	if (!(str = malloc((len + 1) * sizeof(*str))))
		return (0);
	i = 0;
	while (start + i < j && i < len)
	{
		str[i] = s[start + i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

int		ft_strichr(const char *str, char c)
{
	int i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	if (str && str[i] == c)
		return (i);
	return (-1);
}

size_t	ft_strlen(const char *str)
{
	return (ft_strichr(str, '\0'));
}

char	*ft_strdup(const char *src)
{
	char	*dest;
	int		i;

	i = -1;
	if (!(dest = malloc(sizeof(char) * (ft_strlen(src) + 1))))
		return (NULL);
	while (src[++i])
		dest[i] = src[i];
	dest[i] = '\0';
	return (dest);
}

void	*ft_calloc(size_t count, size_t size)
{
	void			*str;
	unsigned char	*tab;
	size_t			l;

	l = count * size;
	if (!(str = malloc(l)))
		return (0);
	tab = str;
	while (0 < l--)
	{
		*tab = 0;
		tab++;
	}
	return (str);
}
