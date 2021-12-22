/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlepart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 16:21:34 by rlepart           #+#    #+#             */
/*   Updated: 2021/01/16 16:21:36 by rlepart          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_is_in(const char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static int		ft_good_size(const char *str, const char *set)
{
	int	i;
	int	j;

	i = 0;
	while (str[i])
		i++;
	while (i >= 0 && (ft_is_in(set, str[i]) || str[i] == '\0'))
		i--;
	i++;
	j = 0;
	if (i != 0)
	{
		while (ft_is_in(set, str[j]))
			j++;
	}
	return (i - j + 1);
}

char			*ft_strtrim(const char *s1, const char *set)
{
	char	*str;
	size_t	i;
	size_t	j;
	size_t	k;

	if (!s1 || !set)
		return (str = ft_calloc(1, sizeof(*str)));
	i = 0;
	while (s1[i])
		i++;
	k = ft_good_size(s1, set);
	if (!(str = ft_calloc(k, sizeof(*str))))
		return (0);
	i = 0;
	while (ft_is_in(set, s1[i]))
		i++;
	j = 0;
	while (j < k - 1)
	{
		str[j++] = s1[i++];
	}
	str[j] = '\0';
	return (str);
}
