/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_trim.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-kada <mel-kada@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 19:02:27 by rlepart           #+#    #+#             */
/*   Updated: 2021/03/11 21:54:56 by mel-kada         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	*ft_trim(char *str, int start, int end)
{
	char	*head;
	char	*tail;
	char	*ret;

	if (!str || (start >= end) || start < 0 || (size_t)end > ft_strlen(str))
		return (NULL);
	if (!(head = ft_substr(str, 0, start)))
		return (NULL);
	if (!(tail = ft_strdup(str + end)))
	{
		free(head);
		return (NULL);
	}
	ret = ft_strjoin(head, tail);
	free(str);
	free(head);
	free(tail);
	return (ret);
}
