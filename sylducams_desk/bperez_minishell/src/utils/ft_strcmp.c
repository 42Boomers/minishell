/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngeschwi <nathan.geschwind@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 16:17:21 by ngeschwi          #+#    #+#             */
/*   Updated: 2021/10/27 18:05:46 by ngeschwi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	unsigned int	i;

	i = 0;
	while (s1[i] != '\0')
	{
		if (s1[i] > s2[i] || s2[i] == '\0')
			return (1);
		else if (s1[i] < s2[i])
			return (-1);
		i++;
	}
	if (s2[i] != '\0')
		return (-1);
	return (0);
}
