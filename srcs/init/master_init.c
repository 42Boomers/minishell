/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   master_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tglory <tglory@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 18:35:32 by tglory            #+#    #+#             */
/*   Updated: 2021/12/16 23:22:26 by tglory           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_master	*ms_init_master(int ac, char **av, char **evs)
{
	t_master	*master;

	master = malloc(sizeof(t_master));
	if (!master)
	{
		ft_println_red("Error > An error has occured while malloc t_master");
		return (NULL);
	}
	master->garbage = NULL;
	master->cmds = NULL;
	ms_garbage_master_add(master, &(master->cmds), ms_lstclear);
	master->av = av;
	master->ac = ac;
	master->verbose = TRUE;
	master->paths = NULL;
	master->pwd = NULL;
	master->envs = NULL;
	master->old_pwd = NULL;
	master->last_status = 0;
	ms_env_init(master, evs);
	master->hist_file = ft_strjoin(ms_pwd(master), "/.ms_history");
	ms_history_read(master);
	return (master);
}

void	ms_free_master(t_master	*master)
{
	// rl_clear_history();
	clear_history();
	free(master->hist_file);
	ms_env_destroy(master);
	ms_garbage_free(&master->garbage);
	free(master);
}
