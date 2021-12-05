/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_write.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tglory <tglory@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 07:20:57 by tglory            #+#    #+#             */
/*   Updated: 2021/12/05 07:55:46 by tglory           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_write(char **array, int size)
{
	int		i;
	int		j;
	int		k;
	char	*str;
	int		max_size;

	max_size = 1;
	i = 0;
	while (i < size)
	{
		max_size += ft_strlen(array[i]) + 1;
		i++;
	}
	str = malloc(sizeof(char) * max_size);
	if (!str)
		return (1);
	i = 0;
	k = -1;
	while (i < size)
	{
		j = -1;
		while (array[i][++j])
		{
			str[++k] = array[i][j];
		}
		str[++k] = '\n';
		i++;
	}
	write(1, str, max_size - 1);
	free(str);
	return (0);
}
