/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ben <ben@student.42lyon.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 16:41:13 by ngeschwi          #+#    #+#             */
/*   Updated: 2021/11/22 05:44:16 by ben              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strjoin(const char *s1, const char *s2)
{
	int		size_s1;
	int		size_s2;
	int		i;
	char	*strcat;

	i = -1;
	if (s1 == NULL)
		return (ft_strdup((char *)s2));
	if (s2 == NULL)
		return (ft_strdup((char *)s1));
	size_s1 = ft_strlen(s1);
	size_s2 = ft_strlen(s2);
	strcat = malloc(sizeof(char) * (size_s1 + size_s2 + 1));
	if (strcat == NULL)
		return (NULL);
	while (size_s1 > i++)
		strcat[i] = s1[i];
	i = 0;
	while (i < size_s2)
	{
		strcat[size_s1 + i] = s2[i];
		i++;
	}
	strcat[size_s1 + i] = '\0';
	return (strcat);
}
