/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cmd_register.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tglory <tglory@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 22:06:27 by tglory            #+#    #+#             */
/*   Updated: 2021/12/02 23:03:29 by tglory           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Register here all cmds with ms_cmd_register
 * @param master 
 */
void	ms_cmd_register_all(t_master *master)
{
	ms_cmd_register("env", master, ms_cmd_env_register);
}
