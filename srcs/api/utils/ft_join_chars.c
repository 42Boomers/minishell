/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_join_chars.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tglory <tglory@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 22:46:20 by tglory            #+#    #+#             */
/*   Updated: 2021/12/22 23:13:38 by tglory           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	ft_strlen_chars(char **array)
{
	size_t i;

	i = 0;
	while (array[i])
		i++;
	return (i);
}

char	**ft_join_chars(char **array1, char **array2)
{
	char	**out;
	int		i;

	out = malloc(sizeof(char *) * (ft_strlen_chars(array1) + ft_strlen_chars(array2) + 1));
	if (!out)
		return (NULL);
	i = 0;
	while (*array1)
		out[i++] = *array1++;
	while (*array2)
		out[i++] = *array2++;
	out[i] = 0;
	return (out);
}
