/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_ultimate2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrozniec <mrozniec@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/25 09:00:55 by mrozniec          #+#    #+#             */
/*   Updated: 2021/12/25 09:58:32 by mrozniec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_skip2(const char *s, int n)
{
	n++;
	while (s[n] && s[n] != '\"')
	{
		if (s[n + 1] && s[n] == '\\')
			n += 2;
		else
			n++;
	}
	return (n);
}

int ft_ttabcrea2(const char *s, int n, char c, int *line)
{
	int		not_used[2];

	not_used[1] = 0;
	while (s[n] == c)
		n++;
	if (s[n] != c && s[n] != '\0')
		(*line)++;
	while (s[n] != c && s[n] != '\0' && s[n] != '|' && s[n] != '<' && \
		s[n] != '>')
	{
		n = ft_skip(s, n, not_used);
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

int ft_fillstr2(const char *s, int n, char c, int m[4])
{
	m[0] = n;
	m[1] = 0;
	m[2] = 0;
	m[3] = 0;
	if (s[n] != '|' && s[n] != '<' && s[n] != '>')
	{
		while (s[n] != '\0' && s[n] != c && s[n] != '|' && s[n] != '<' && \
			s[n] != '>')
		{
			n = ft_skip(s, n, m);
			if (s[n] == '\'' || s[n] == '\"')
				m[2] += 2;
			n++;
		}
	}
	else if (s[n] == '|' || (s[n] == '<' && s[n + 1] != '<') || \
	(s[n] == '>' && s[n + 1] != '>'))
		n++;
	else if ((s[n] == '<' && s[n + 1] == '<') || \
	(s[n] == '>' && s[n + 1] == '>'))
		n += 2;
	m[0] = n - m[0];
	return (n);
}

void ft_fillstr3(const char *s, int n, char *strs, int m[4])
{
	m[1] = m[0];
	while ((m[0] - m[2]) > 0)
	{
		while (s[n - m[0]] == '\"' || s[n - m[0]] == '\'')
		{
			if (s[n - m[0]] == '\'')
				m[3] = !m[3];
			n++;
		}
		if (s[n - m[0]] == '$' && m[3] != 0)
		{
			strs[m[1] - m[0]] = '\\';
			m[1]++;
			strs[m[1] - m[0]] = s[n - m[0]];
		}
		else
			strs[m[1] - m[0]] = s[n - m[0]];
		m[0]--;
	}
	strs[m[1] - m[0]] = '\0';
}

int ft_split_ultimate2(const char *s, int n, char c)
{
	int		not_used[2];

	not_used[1] = 0;
	if (s[n] == '|' || s[n] == '<' || s[n] == '>')
	{
		n++;
		if ((s[n] == '<' && s[n - 1] == '<') || (s[n] == '>' && \
				s[n - 1] == '>'))
			n++;
	}
	else
	{
		n = ft_skip(s, n, not_used);
		while (s[n] != c && s[n] != '\0' && s[n] != '|' && s[n] != '<' && \
			s[n] != '>')
			n++;
	}
	return (n);
}
