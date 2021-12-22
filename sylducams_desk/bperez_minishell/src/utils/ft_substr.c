/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ben <ben@student.42lyon.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 17:06:34 by bperez            #+#    #+#             */
/*   Updated: 2021/11/04 02:05:07 by ben              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char	*s2;
	size_t	slen;
	size_t	i;

	slen = ft_strlen(s);
	if (slen < len)
		len = slen - start;
	s2 = (char *)ft_calloc(len + 1, sizeof(char));
	if (s2 && start < slen)
	{
		s += start;
		i = 0;
		while (s[i] && len--)
		{
			s2[i] = s[i];
			i++;
		}
	}
	return (s2);
}
