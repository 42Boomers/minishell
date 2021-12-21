/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_iter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tglory <tglory@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 17:53:38 by tglory            #+#    #+#             */
/*   Updated: 2021/12/21 18:02:21 by tglory           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	ft_str_isall(char *str, int	(is_good)(char c))
{
	if (!str)
		return (FALSE);
	while (*str++)
	{
		if (!is_good(*str))
			return (FALSE);
	}
	return (TRUE);
}
