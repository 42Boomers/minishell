/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblache <jblache@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 17:54:07 by jblache           #+#    #+#             */
/*   Updated: 2021/12/29 18:34:47 by jblache          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_realloc(void *ptr, size_t new_size, size_t old_size)
{
	char	*newptr;

	newptr = ft_calloc(new_size, sizeof(unsigned char));
	if (!(newptr))
		return (NULL);
	if (ptr)
	{
		if (old_size > new_size)
			old_size = new_size;
		ft_memcpy(newptr, ptr, old_size);
		free(ptr);
	}
	return (newptr);
}
