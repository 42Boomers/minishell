/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblache <jblache@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 03:50:38 by jblache           #+#    #+#             */
/*   Updated: 2021/12/24 19:53:42 by jblache          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	ft_strisfullof(char *str, char c)
{
	if (!str)
		return (FALSE);
	while (*str && *str == c)
		str++;
	if (!str)
		return (TRUE);
	return (FALSE);
}
