/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_write.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tglory <tglory@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 07:20:57 by tglory            #+#    #+#             */
/*   Updated: 2021/12/07 05:57:48 by tglory           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_write(char **array, int size)
{
	int		i;
	int		j;
	int		k;
	char	*str;
	int		max_size;

	max_size = 1;
	i = 0;
	while (i < size)
		max_size += ft_strlen(array[i++]) + 1;
	str = malloc(sizeof(char) * max_size);
	if (!str)
		return ;
	i = -1;
	k = -1;
	while (++i < size)
	{
		j = -1;
		while (array[i][++j])
			str[++k] = array[i][j];
		str[++k] = '\n';
	}
	write(1, str, max_size - 1);
	free(str);
}
