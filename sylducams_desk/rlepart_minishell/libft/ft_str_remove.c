/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_remove.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-kada <mel-kada@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 16:53:02 by rlepart           #+#    #+#             */
/*   Updated: 2021/03/03 22:00:55 by mel-kada         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_str_remove(char **str, int index)
{
	int		i[2];
	char	**dup;

	i[0] = 0;
	while (str && str[i[0]])
		i[0]++;
	if (!(dup = malloc(sizeof(*dup) * (i[0] + 1 - (i[0] < index)))))
		return (NULL);
	i[0] = 0;
	i[1] = 0;
	while (str && str[i[0]])
	{
		if (i[0] != index)
		{
			dup[i[1]] = str[i[0]];
			i[1]++;
		}
		else
			free(str[i[0]]);
		i[0]++;
	}
	dup[i[1]] = NULL;
	if (str)
		free(str);
	return (dup);
}
