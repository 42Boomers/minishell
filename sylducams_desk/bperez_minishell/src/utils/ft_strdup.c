/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngeschwi <nathan.geschwind@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 16:19:54 by ngeschwi          #+#    #+#             */
/*   Updated: 2021/10/28 16:21:12 by ngeschwi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strdup(char *src)
{
	char	*copy;
	int		size_src;
	int		i;

	i = 0;
	size_src = ft_strlen(src);
	copy = malloc(sizeof(char) * (size_src + 1));
	if (copy == NULL)
		return (NULL);
	if (size_src == 0)
	{
		copy[0] = '\0';
		return (copy);
	}
	while (src[i] != '\0')
	{
		copy[i] = src[i];
		i++;
	}
	if (size_src != 0)
		copy[i] = '\0';
	return (copy);
}
