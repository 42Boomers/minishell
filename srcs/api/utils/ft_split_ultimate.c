/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_ultimate.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tglory <tglory@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 18:02:37 by mrozniec          #+#    #+#             */
/*   Updated: 2021/12/24 18:35:50 by tglory           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**ft_ttabcrea(char const *s, char c)
{
	int		n;
	int		line;
	char	**strs;

	n = 0;
	line = 0;
	while (s[n] != '\0')
		n = ft_ttabcrea2(s, c, n, &line);
	strs = malloc(sizeof(char *) * (line + 1));
	if (!strs)
		return (NULL);
	return (strs);
}

static char	*ft_fillstr(char const *s, char c, int n)
{
	int		m[4];
	char	*strs;

	m[0] = n;
	m[2] = 0;
	m[3] = 0;
	if (!ft_fillstr2(s, c, &n, m))
	{
		if (s[n] == '|' || (s[n] == '<' && s[n + 1] != '<') || \
		(s[n] == '>' && s[n + 1] != '>'))
			n++;
		else if ((s[n] == '<' && s[n + 1] == '<') || \
		(s[n] == '>' && s[n + 1] == '>'))
			n += 2;
	}
	m[0] = n - m[0];
	strs = malloc(sizeof(char) * (m[0] + 1));
	if (!strs)
		return (NULL);
	m[1] = m[0];
	return (ft_fillstr3(s, strs, &n, m));
}

static char	**ft_free_error(char **strs, int line)
{
	while (line > 0)
	{
		free(strs[line - 1]);
		line--;
	}
	free(strs);
	return (NULL);
}

char	**ft_split_ultimate(char const *s, char c)
{
	int		n;
	int		line;
	char	**strs;

	strs = ft_ttabcrea(s, c);
	n = 0;
	line = 0;
	while (s[n] != '\0')
	{
		while (s[n] == c)
			n++;
		if (s[n] != '\0' && s[n] != c)
		{
			line++;
			strs[line - 1] = ft_fillstr(s, c, n);
			if (!strs[line - 1])
				return (ft_free_error(strs, line - 1));
		}
		n = ft_split_ultimate2(s, c, n);
	}
	strs[line] = NULL;
	return (strs);
}
