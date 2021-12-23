/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-kada <mel-kada@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/03 19:39:36 by mel-kada          #+#    #+#             */
/*   Updated: 2021/03/11 15:44:45 by mel-kada         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static	int		get_nbr_words(char const *s, char c)
{
	int		words;
	int		separator;
	int		i;

	i = -1;
	words = 0;
	separator = 0;
	while (s[++i])
	{
		if (s[i] == c && !ft_is_ignored(s, c, i))
			separator = 0;
		else if (separator == 0)
		{
			separator = 1;
			words++;
		}
	}
	return (words);
}

static	int		nbrchar(char const *s, char c, int i)
{
	int		nbr;

	nbr = 0;
	while (s[i] && ft_isspace(s[i]))
		i++;
	while (s[i] && (s[i] != c || ft_is_ignored(s, c, i)))
	{
		nbr++;
		i++;
	}
	return (nbr);
}

static	char	**ft_free(char **str, int max)
{
	int i;

	i = 0;
	while (i < max)
	{
		free(str[i]);
		i++;
	}
	free(str);
	str = NULL;
	return (str);
}

static	char	**ft_str(char **str, char const *s, char c, int words)
{
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	while (i < words)
	{
		if (!(str[i] = (char *)malloc(sizeof(char) * nbrchar(s, c, j) + 1)))
			return (ft_free(str, i));
		k = 0;
		while (ft_isspace(s[j]) || (s[j] == c && !ft_is_ignored(s, c, j)))
			j++;
		while (s[j] && (s[j] != c || ft_is_ignored(s, c, j)))
		{
			str[i][k] = s[j];
			j++;
			k++;
		}
		str[i][k] = 0;
		j++;
		i++;
	}
	str[i] = 0;
	return (str);
}

char			**ft_split_args(char *s, char c)
{
	char	**ptr;
	int		words;

	if (!s)
		return (NULL);
	words = get_nbr_words(s, c);
	if (!(ptr = (char **)malloc(sizeof(char *) * (words + 1))))
		return (NULL);
	return (ft_str(ptr, s, c, words));
}
