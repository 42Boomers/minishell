/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_ultimate.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sylducam <sylducam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 18:02:37 by mrozniec          #+#    #+#             */
/*   Updated: 2021/12/25 09:56:36 by mrozniec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_skip(const char *s, int n, int *dollars)
{
	while (s[n] && s[n + 1] && s[n] == '\\')
		n += 2;
	if (s[n] == '\"')
		n = ft_skip2(s, n);
	if (s[n] == '\'')
	{
		n++;
		while (s[n] && s[n] != '\'')
		{
			if (s[n] == '$')
				dollars[1] += 1;
			if (s[n + 1] && s[n] == '\\')
				n += 2;
			else
				n++;
		}
	}
	return (n);
}

static char	**ft_ttabcrea(char const *s, char c)
{
	int		n;
	int		line;
	char	**strs;

	n = 0;
	line = 0;
	while (s[n] != '\0')
		n = ft_ttabcrea2(s, n, c, &line);
	strs = malloc(sizeof(char *) * (line + 1));
	if (!strs)
		return (NULL);
	return (strs);
}

static char	*ft_fillstr(char const *s, char c, int n)
{
	int		m[4];
	char	*strs;

	n = ft_fillstr2(s, n, c, m);
	strs = malloc(sizeof(char) * (m[0] + 1 + m[1] - m[2]));
	if (!strs)
		return (NULL);
	ft_fillstr3(s, n, strs, m);
	return (strs);
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
		n = ft_split_ultimate2(s, n, c);
	}
	strs[line] = NULL;
	return (strs);
}
