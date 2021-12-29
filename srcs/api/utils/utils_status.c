/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_status.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblache <jblache@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 23:11:28 by jblache           #+#    #+#             */
/*   Updated: 2021/12/16 16:46:01 by jblache          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_set_status(t_master *master, int status)
{
	if (status == 0 || status == 1)
		master->last_status = !status;
	else
		master->last_status = status;
}
