/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sylducam <sylducam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 22:36:30 by tglory            #+#    #+#             */
/*   Updated: 2021/12/22 13:52:59 by sylducam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ms_prefix_get(t_master *master)
{
	char	*out;
	char	*prefix;

	if (!master->last_status)
		prefix = "\e[0;32m➜ \e[36m"; // syl : whaaaat ? me need explanation on syntax
	else
		prefix = "\e[0;31m➜ \e[36m";
	out = ft_strjoin_plus(prefix, ms_pwd(master), " > \e[0;33m"); // syl : need explanation too
	return (out);
}
