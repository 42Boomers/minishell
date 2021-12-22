/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: neben <neben@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 18:48:16 by bperez            #+#    #+#             */
/*   Updated: 2021/11/07 22:26:33 by neben            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_set(const char c)
{
	if (' ' == c)
		return (1);
	return (0);
}

char	*ft_strtrim(const char *s1)
{
	size_t	len;

	while (*s1 && check_set(*s1))
		s1++;
	len = ft_strlen(s1);
	while (len && check_set(s1[len - 1]))
		len--;
	return (ft_strndup(s1, len));
}
