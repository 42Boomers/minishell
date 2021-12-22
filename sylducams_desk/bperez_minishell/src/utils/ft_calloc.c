/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ben <ben@student.42lyon.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 19:20:54 by bperez            #+#    #+#             */
/*   Updated: 2021/11/04 02:04:48 by ben              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <stdlib.h>

void	*ft_calloc(const size_t count, const size_t size)
{
	void	*ptr;
	size_t	len;

	ptr = NULL;
	len = size * count;
	if (len > 0)
	{
		ptr = malloc(len);
		if (ptr)
			ft_bzero(ptr, len);
	}
	return (ptr);
}
