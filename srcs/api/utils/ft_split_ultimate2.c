/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_ultimate2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tglory <tglory@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 18:02:37 by mrozniec          #+#    #+#             */
/*   Updated: 2021/12/24 18:36:13 by tglory           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_skip(const char *s, int n)
{
	while (s[n] && s[n + 1] && s[n] == '\\')
		n += 2;
	if (s[n] == '\"')
	{
		n++;
		while (s[n] && s[n] != '\"')
		{
			if (s[n + 1] && s[n] == '\\')
				n += 2;
			else
				n++;
		}
	}
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

int	ft_split_ultimate2(char const *s, char c, int n)
{
	if (s[n] == '|' || s[n] == '<' || s[n] == '>')
	{
		n++;
		if ((s[n] == '<' && s[n - 1] == '<') || (s[n] == '>' && \
			s[n - 1] == '>'))
			n++;
	}
	else
	{
		n = ft_skip(s, n);
		while (s[n] != c && s[n] != '\0' && s[n] != '|' && s[n] != '<' && \
		s[n] != '>')
			n++;
	}
	return (n);
}

char	*ft_fillstr3(char const *s, char *strs, int *n, int *m)
{
	while ((m[0] - m[2]) > 0)
	{
		while (s[*n - m[0]] == '\"' || s[*n - m[0]] == '\'')
		{
			if (s[*n - m[0]] == '\'')
				m[3] = !m[3];
			n++;
		}
		if (s[*n - m[0]] == '$' && m[3] != 0)
		{
			strs[m[1] - m[0]] = '\\';
			m[1]++;
			strs[m[1] - m[0]] = s[*n - m[0]];
		}
		else
			strs[m[1] - m[0]] = s[*n - m[0]];
		m[0]--;
	}
	strs[m[1]] = '\0';
	return (strs);
}

t_bool	ft_fillstr2(char const *s, char c, int *n, int *m)
{
	if (s[*n] != '|' && s[*n] != '<' && s[*n] != '>')
	{
		while (s[*n] != '\0' && s[*n] != c && s[*n] != '|' && s[*n] != '<' && \
			s[*n] != '>')
		{
			*n = ft_skip(s, *n);
			if (s[*n] == '\'' || s[*n] == '\"')
				m[2] += 2;
			(*n)++;
		}
		return (TRUE);
	}
	return (FALSE);
}

int	ft_ttabcrea2(char const *s, char c, int n, int *line)
{
	while (s[n] == c)
		n++;
	if (s[n] != c && s[n] != '\0')
		(*line)++;
	while (s[n] != c && s[n] != '\0' && s[n] != '|' && s[n] != '<' && \
			s[n] != '>')
	{
		n = ft_skip(s, n);
		n++;
	}
	if (s[n] == '|' || s[n] == '<' || s[n] == '>')
		(*line)++;
	if (s[n] == '|' || s[n] == '<' || s[n] == '>')
		n++;
	if ((s[n] == '<' && s[n - 1] == '<') || (s[n] == '>' && \
	s[n - 1] == '>'))
		n++;
	return (n);
}
