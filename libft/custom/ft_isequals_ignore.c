/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isequals_ignore.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tglory <tglory@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 03:39:04 by tglory            #+#    #+#             */
/*   Updated: 2021/12/05 03:40:18 by tglory           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "custom.h"

int	ft_isequals_ignore(char *str1, char *str2)
{
	size_t	i;

	i = 0;
	while ((str1[i]) || (str2[i]))
	{
		if (ft_tolower(str1[i]) != ft_tolower(str2[i]))
			return (0);
		i++;
	}
	return (1);
}
