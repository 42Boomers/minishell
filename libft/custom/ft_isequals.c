/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isequals.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tglory <tglory@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 03:40:40 by tglory            #+#    #+#             */
/*   Updated: 2021/12/05 03:43:12 by tglory           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "custom.h"

int	ft_isequals(char *str1, char *str2)
{
	size_t	size1;
	size_t	size2;

	size1 = ft_strlen(str1);
	size2 = ft_strlen(str2);
	if (size1 != size2 || ft_strncmp(str1, str2, size1 + 1))
		return (0);
	return (1);
}
