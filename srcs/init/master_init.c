/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   master_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tglory <tglory@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 18:35:32 by tglory            #+#    #+#             */
/*   Updated: 2021/12/07 01:34:00 by tglory           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_master	*ms_init_master(int av, char **ag, char **ev)
{
	t_master	*master;

	master = malloc(sizeof(t_master));
	if (!master)
	{
		ft_println_red("Error > An error has occured while malloc t_master");
		return (NULL);
	}
	master->free_function = NULL;
	master->cmds = NULL;
	ms_garbage_add(&master->free_function, &(master->cmds), ms_lstclear);
	master->av = av;
	master->ag = ag;
	master->verbose = TRUE;
	master->paths = NULL;
	master->pwd = NULL;
	master->old_pwd = NULL;
	master->last_status = 0;
	master->hist_file = ".ms_history";
	ms_env_init(master, ev);
	mv_history_read(master);
	return (master);
}

void	ms_free_master(t_master	*master)
{
	ms_garbage_free(&master->free_function);
	free(master);
}

/**
 * @brief Register here all cmds with ms_cmd_register
 * @param master 
 */
void	ms_cmd_register_all(t_master *master)
{
	ms_cmd_register("help", "This message",
		master, ms_cmd_help_register);
	ms_cmd_register("pwd", "Show current path",
		master, ms_cmd_pwd_register);
	ms_cmd_register("env", "Show all environnement variable",
		master, ms_cmd_env_register);
	ms_cmd_register("echo", "Print arguments",
		master, ms_cmd_echo_register);
	ms_cmd_register("cd", "Move into other directory",
		master, ms_cmd_cd_register);
}
