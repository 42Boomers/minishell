/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_join_free.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlepart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 17:12:30 by rlepart           #+#    #+#             */
/*   Updated: 2021/02/20 11:46:48 by rlepart          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_join_free(char *s1, char *s2, int i)
{
	char	*s;

	if (!s1 && !s2)
		return (NULL);
	else if (!s1)
		s = ft_strdup(s2);
	else if (!s2)
		s = ft_strdup(s1);
	else
		s = ft_strjoin(s1, s2);
	if (i > 1)
		free(s1);
	if (i % 2)
		free(s2);
	return (s);
}
