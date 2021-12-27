/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_parse3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tglory <tglory@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 02:35:52 by tglory            #+#    #+#             */
/*   Updated: 2021/12/27 22:51:38 by tglory           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	ms_env_parse_tilde(t_env_parse *ep)
{
	char	*home;

	if (*(ep->str) && *(ep->str) == '~')
	{
		home = ft_strdup(ms_env_get(ep->master, "HOME"));
		ft_str_add(ep->build, home);
		(ep->str)++;
		ep->i++;
		return (TRUE);
	}
	return (FALSE);
}
