/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tglory <tglory@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 22:36:30 by tglory            #+#    #+#             */
/*   Updated: 2021/12/21 11:20:45 by tglory           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ms_prefix_get(t_master *master)
{
	char	*out;
	char	*prefix;

	if (!master->last_status)
		prefix = "\e[0;32m➜ \e[36m";
	else
		prefix = "\e[0;31m➜ \e[36m";
	out = ft_strjoin_plus(prefix, ms_pwd(master), " > \e[0;33m");
	return (out);
}
