/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_ultimate2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrozniec <mrozniec@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/25 09:00:55 by mrozniec          #+#    #+#             */
/*   Updated: 2021/12/26 20:29:58 by mrozniec         ###   ########.fr       */
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

char	*ft_fillstr2(t_master *master, const char *s, char *strs, int m[3])
{
	char	*strs_old;
	char	*temp;

	strs_old = strs;
	temp = ft_substr(s, m[0], m[2] - m[0]);
	m[0] = m[2] + 1;
	if (master && ft_strlen(temp) > 0 && m[1] == 0)
		temp = ms_env_parse(master, temp);
	if (s[m[2]] == '\'')
		m[1] = !m[1];
	if (temp)
		strs = ft_strjoin(strs_old, temp);
	if (temp)
		free(strs_old);
	free(temp);
	return (strs);
}

char *ft_fillstr3(const char *s, char *strs, int n, int m[3])
{
	if (s[n] == '|' || (s[n] == '<' && s[n + 1] != '<') || \
	(s[n] == '>' && s[n + 1] != '>'))
		strs = ft_substr(s, m[0], (++n) - m[0]);
	else if ((s[n] == '<' && s[n + 1] == '<') || \
	(s[n] == '>' && s[n + 1] == '>'))
	{
		n += 2;
		strs = ft_substr(s, m[0], n - m[0]);
	}
	return (strs);
}

int ft_split_ultimate2(const char *s, int n, char c)
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
