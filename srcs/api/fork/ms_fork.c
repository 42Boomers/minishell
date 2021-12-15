/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_fork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tglory <tglory@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 10:07:29 by tglory            #+#    #+#             */
/*   Updated: 2021/12/13 17:49:52 by mrozniec         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ms_child(t_master *master, char *command, char **args)
{
	if (!ms_cmd_os(master, command, args))
	{
		mv_set_status(master, FALSE);
		printf("\e[31mminishell: %s: command not found\n\e[0m", command);
	}
}

static int	ms_wait_fork(pid_t fork_id, char **args, int *redir)
{
	int	*status;

	status = NULL;
	waitpid(fork_id, status, 0);
	if (redir[0] > 0)
		close(redir[0]);
	if (redir[1] > 0)
		close(redir[1]);
	free(redir);
	return (ft_pipe_check(args));
}

static char	*ms_next_fork(int pip_rec, int pip_end[2], int *fd_in, char ***args)
{
	char	*command;

	close(pip_end[1]);
	*fd_in = pip_end[0];
	command = (*args)[pip_rec];
	*args = &((*args)[pip_rec + 1]);
	ms_check_redir(&command, *args);
	return (command);
}

static int	*ms_fork_init(const int *fd_in, int pip_end[2], char **args, pid_t \
*fork_id)
{
	int	pip_rec;
	int	*redir;
	int i;

	redir = malloc(2*sizeof(int));
	if (!redir)
	{
		ft_println_red("Error > An error has occured while malloc creation");
		return (NULL);
	}
	ms_red_in_out(args, redir);
	*fork_id = fork();
	if (*fork_id < 0)
	{
		ft_println_red("Error > An error has occured while fork creation");
		return (NULL);
	}
	if (*fork_id == 0)
	{
		pip_rec = ft_pipe_check(args);
		if (redir[0] > 0)
			dup2(redir[0], 0);
		else
			dup2(*fd_in, 0);
		if (redir[1] > 0)
			close(pip_end[1]);
		if (redir[1] > 0)
			dup2(redir[1], 1);
		else if (pip_rec > 0)
			dup2(pip_end[1], 1);
		close(pip_end[0]);
	}
	return (redir);
}

void	ms_fork(t_master *master, char *command, char **args)
{
	int		pip_end[2];
	int		fd_in;
	int		*redir;
	int		pip_rec;
	pid_t	fork_id;

	pip_rec = 1;
	while (pip_rec > 0)
	{
		if (ms_error_pipe(pip_end) == -1)
			return ;
		redir = ms_fork_init(&fd_in, pip_end, args, &fork_id);
		if (fork_id == 0)
			ms_child(master, command, args);
		else
		{
			pip_rec = ms_wait_fork(fork_id, args, redir);
			if (pip_rec > 0)
				command = ms_next_fork(pip_rec, pip_end, &fd_in, &args);
		}
	}
}
