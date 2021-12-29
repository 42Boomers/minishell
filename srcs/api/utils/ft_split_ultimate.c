/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_ultimate.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblache <jblache@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 18:02:37 by mrozniec          #+#    #+#             */
/*   Updated: 2021/12/29 17:08:39 by jblache          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_skip(const char *s, int n)
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

static char	*ft_fillstr(t_master *master, char const *s, char c, int *n)
{
	int		m[4];
	char	*strs;

	strs = ft_init_fillstr(m, *n);
	if (s[*n] != '|' && s[*n] != '<' && s[*n] != '>')
	{
		while (s[*n] != '\0' && (m[3] != 0 || (s[*n] != c && s[*n] != '|' \
		&& s[*n] != '<' && s[*n] != '>')))
		{
			if (s[*n] == '\\')
				*n += 2;
			if (s[*n] == '\'' || s[*n] == '\"')
			{
				m[2] = *n;
				strs = ft_fillstr2(master, s, strs, m);
				m[3] = !m[3];
			}
			(*n)++;
		}
		m[2] = *n;
		strs = ft_fillstr2(master, s, strs, m);
	}
	else
		strs = ft_fillstr3(s, strs, n, m);
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

char	**ft_split_ultimate(t_master *master, char const *s, char c)
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
			strs[line - 1] = ft_fillstr(master, s, c, &n);
			if (!strs[line - 1])
				return (ft_free_error(strs, line - 1));
		}
	}
	strs[line] = NULL;
	return (strs);
}
