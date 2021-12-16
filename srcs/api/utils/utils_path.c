/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tglory <tglory@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 22:36:30 by tglory            #+#    #+#             */
/*   Updated: 2021/12/16 23:11:46 by tglory           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ms_prefix_get(t_master *master)
{
	char	*out;

	out = ft_strjoin_plus("\e[36m", ms_pwd(master)," > \e[96m");
	return (out);
}
