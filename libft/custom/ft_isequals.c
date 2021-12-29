/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isequals.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblache <jblache@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 03:40:40 by jblache           #+#    #+#             */
/*   Updated: 2021/12/29 18:34:47 by jblache          ###   ########lyon.fr   */
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
