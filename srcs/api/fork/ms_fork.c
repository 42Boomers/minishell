/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_fork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tglory <tglory@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 10:07:29 by tglory            #+#    #+#             */
/*   Updated: 2021/12/05 16:47:52 by tglory           ###   ########lyon.fr   */
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
/*
** version 1.0 working with one pipe
** need some modification to work with more pipe
*/

/*
void	ms_fork2(t_master *master, char *command, char **args, int pipe_check)
{
	int		pip_end[2];
	int		*status;
	int		pip_rec;
	pid_t	fork_id;
	pid_t	pip_fork_id;

	//printf("i was here %d", pipe_check);
	if (pipe_check > 0)
	{
		if (pipe(pip_end) == -1)
		{
			ft_println_red("Error > An error has occured while pipe creation");
			return ;
		}
	}
	fork_id = fork();
	if (fork_id < 0)
	{
		ft_println_red("Error > An error has occured while fork creation");
		return ;
	}
	if (fork_id == 0)
	{
		if (pipe_check > 0)
		{
			close(pip_end[0]);
			dup2(pip_end[1], 1);
		}
		ms_child(master, command, args);
	}
	else
	{
		if (pipe_check > 0)
		{
			pip_fork_id = fork();
			if (pip_fork_id < 0)
			{
				ft_println_red("Error > An error has occured while fork creation");
				return ;
			}
			if (pip_fork_id == 0)
			{
				close(pip_end[1]);
				dup2(pip_end[0], 0);
				pip_rec = ft_pipe_check(&args[pipe_check]);
				if (pip_rec > 0)
					ms_fork2(master, args[pipe_check], &args[pipe_check + 1], \
					pip_rec);
				else if (pip_rec == 0)
					ms_child(master, args[pipe_check], &args[pipe_check + 1]);
			}
		}
	}
	status = NULL;
	if (pipe_check > 0)
	{
		close(pip_end[0]);
		close(pip_end[1]);
		waitpid(pip_fork_id, status, 0);
	}
	waitpid(fork_id, status, 0);
}*/
void	ms_fork2(t_master *master, char *command, char **args)
{
	int		pip_end[2];
	int		*status;
	int		pip_rec;
	pid_t	fork_id;

	pip_rec = 5;
	//printf("i was here %d", pipe_check);
	while (pip_rec > 0)
	{
		if (pipe(pip_end) == -1)
		{
			ft_println_red("Error > An error has occured while pipe creation");
			return ;
		}
	}
	fork_id = fork();
	if (fork_id < 0)
	{
		ft_println_red("Error > An error has occured while fork creation");
		return ;
	}
	if (fork_id == 0)
	{
		if (pipe_check > 0)
		{
			close(pip_end[0]);
			dup2(pip_end[1], 1);
		}
		ms_child(master, command, args);
	}
	else
	{
		if (pipe_check > 0)
		{
			pip_fork_id = fork();
			if (pip_fork_id < 0)
			{
				ft_println_red("Error > An error has occured while fork creation");
				return ;
			}
			if (pip_fork_id == 0)
			{
				close(pip_end[1]);
				dup2(pip_end[0], 0);
				pip_rec = ft_pipe_check(&args[pipe_check]);
				if (pip_rec > 0)
					ms_fork2(master, args[pipe_check], &args[pipe_check + 1], \
					pip_rec);
				else if (pip_rec == 0)
					ms_child(master, args[pipe_check], &args[pipe_check + 1]);
			}
		}
	}
	status = NULL;
	if (pipe_check > 0)
	{
		close(pip_end[0]);
		close(pip_end[1]);
		waitpid(pip_fork_id, status, 0);
	}
	waitpid(fork_id, status, 0);
}