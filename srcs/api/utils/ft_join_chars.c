/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_join_chars.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tglory <tglory@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 22:46:20 by tglory            #+#    #+#             */
/*   Updated: 2021/12/22 23:05:00 by tglory           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	ft_strlen_chars(char **array)
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

void	ft_join_chars_test()
{
	char **out;
	char *array1[4];
	char *array2[11];
	int		i;

	i = 0;
	array1[i++] = "HELLO";
	array1[i++] = "WORLD";
	array1[i++] = "!";
	array1[i] = NULL;
	i = 0;
	array2[i++] = "Ceci";
	array2[i++] = "est";
	array2[i++] = "un";
	array2[i++] = "test";
	array2[i++] = "qui";
	array2[i++] = "va";
	array2[i++] = "tres";
	array2[i++] = "bien";
	array2[i++] = "fonctionner";
	array2[i++] = "?";
	array2[i] = NULL;
	
	out = ft_join_chars(array1, array2);
	ms_write(out, ft_strlen_chars(out));
}
