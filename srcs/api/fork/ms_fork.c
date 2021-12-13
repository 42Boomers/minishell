/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_fork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tglory <tglory@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 10:07:29 by tglory            #+#    #+#             */
/*   Updated: 2021/12/12 13:01:49 by mrozniec         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
void	ms_fork(t_master *master, void child(t_master *))
{
	pid_t	cpid;
	pid_t	wpid;
	int		status;

	cpid = fork();
	if (cpid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (cpid == 0)
	{
		child(master);
	}
	else
	{
		status = -1;
		while (status == -1 || (!WIFEXITED(status) && !WIFSIGNALED(status)))
		{
			wpid = waitpid(cpid, &status, WUNTRACED | WCONTINUED);
			if (wpid == -1)
			{
				perror("waitpid");
				exit(EXIT_FAILURE);
			}
			if (WIFEXITED(status))
				printf("DEBUG terminé, code=%d\n", WEXITSTATUS(status));
			else if (WIFSIGNALED(status))
				printf("DEBUG tué par le signal %d\n", WTERMSIG(status));
			else if (WIFSTOPPED(status))
				printf("DEBUG arrêté par le signal %d\n", WSTOPSIG(status));
			else if (WIFCONTINUED(status))
				printf("DEBUG relancé\n");
		}
	}
}
*/

static void	ms_child(t_master *master, char *command, char **args)
{
	if (!ms_cmd_os(master, command, args))
	{
		mv_set_status(master, FALSE);
		printf("\e[31mminishell: %s: command not found\n\e[0m", command);
	}
}

static int	ms_wait_fork(pid_t fork_id, char **args)
{
	int	*status;

	status = NULL;
	waitpid(fork_id, status, 0);
	return (ft_pipe_check(args));
}

static char	*ms_next_fork(int pip_rec, int pip_end[2], int *fd_in, char ***args)
{
	char	*command;

	close(pip_end[1]);
	*fd_in = pip_end[0];
	command = (*args)[pip_rec];
	*args = &((*args)[pip_rec + 1]);
	return (command);
}

static void	ms_fork_init(const int *fd_in, int pip_end[2], char **args, pid_t \
*fork_id)
{
	int	pip_rec;

	*fork_id = fork();
	if (*fork_id < 0)
	{
		ft_println_red("Error > An error has occured while fork creation");
		return ;
	}
	if (*fork_id == 0)
	{
		dup2(*fd_in, 0);
		pip_rec = ft_pipe_check(args);
		if (pip_rec > 0)
			dup2(pip_end[1], 1);
		close(pip_end[0]);
	}
}

void	ms_fork2(t_master *master, char *command, char **args)
{
	int		pip_end[2];
	int		fd_in;
	int		pip_rec;
	pid_t	fork_id;

	fd_in = 0;
	pip_rec = 1;
	while (pip_rec > 0)
	{
		if (pipe(pip_end) == -1)
		{
			ft_println_red("Error > An error has occured while pipe creation");
			return ;
		}
		ms_fork_init(&fd_in, pip_end, args, &fork_id);
		if (fork_id == 0)
			ms_child(master, command, args);
		else
		{
			pip_rec = ms_wait_fork(fork_id, args);
			if (pip_rec > 0)
				command = ms_next_fork(pip_rec, pip_end, &fd_in, &args);
		}
	}
}
