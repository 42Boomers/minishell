/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tglory <tglory@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 02:48:55 by tglory            #+#    #+#             */
/*   Updated: 2021/12/05 04:19:38 by tglory           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	ms_test_cmd(t_master *master)
{
	printf("\nenv\n\n");
	ms_cmd_launch(master, "env", NULL, 0);
	printf("\npwd\n\n");
	ms_cmd_launch(master, "pwd", NULL, 0);
	printf("\nhelp\n\n");
	ms_cmd_launch(master, "help", NULL, 0);
	//ms_launch_at_start(master);
	return (TRUE);
}
