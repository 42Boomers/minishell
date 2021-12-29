/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_write.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblache <jblache@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 07:20:57 by jblache           #+#    #+#             */
/*   Updated: 2021/12/29 14:53:31 by jblache          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_write2(int i, char *str, int j)
{
	write(i, str, j);
	free(str);
}

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
		j = 0;
		if (ft_strchr(&array[i][j], '=') == NULL)
			continue ;
		while (array[i][j])
			str[++k] = array[i][j++];
		str[++k] = '\n';
	}
	ms_write2(1, str, max_size - 1);
}
