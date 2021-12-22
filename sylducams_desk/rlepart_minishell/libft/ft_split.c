/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlepart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 16:20:32 by rlepart           #+#    #+#             */
/*   Updated: 2021/01/16 16:20:33 by rlepart          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_len(const char *s, char c)
{
	int	i;
	int	k;

	k = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] != c && s[i] != '\0')
		{
			k++;
			while (s[i] != c && s[i] != '\0')
				i++;
			while (s[i] == c && s[i] != '\0')
				i++;
		}
		else
			i++;
	}
	return (k);
}

static char		*make_str(char const *s, char c)
{
	char	*str;
	int		i;
	int		j;

	j = 0;
	while (s[j] && s[j] != c)
		j++;
	if (!(str = ft_calloc(j + 1, sizeof(*str))))
		return (0);
	i = 0;
	while (i < j)
	{
		str[i] = s[i];
		i++;
	}
	str[j] = '\0';
	return (str);
}

static void		ft_clear_str(char **str)
{
	size_t	i;

	i = 0;
	while (str[i])
		free(str[i++]);
	free(str);
}

char			**ft_split(char const *s, char c)
{
	int		i;
	int		j;
	char	**str;

	if (!s)
		return (str = ft_calloc(1, sizeof(*str)));
	if (!(str = ft_calloc(ft_len(s, c) + 1, sizeof(*str))))
		return (0);
	i = -1;
	j = 0;
	if (s[0] != c && s[0])
		str[j++] = make_str(s, c);
	while (s[++i])
		if (s[i + 1] != '\0' && s[i] == c && s[i + 1] != c)
		{
			if (!(str[j] = make_str(s + i + 1, c)))
			{
				ft_clear_str(str);
				return (0);
			}
			j++;
		}
	return (str);
}
