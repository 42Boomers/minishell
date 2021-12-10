/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_os_launch.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tglory <tglory@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 09:35:36 by tglory            #+#    #+#             */
/*   Updated: 2021/12/10 03:01:17 by tglory           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ms_cmd_os_run_parent_verbose(t_master *master, int status)
{
	if (WIFEXITED(status))
		mv_set_status(master, WEXITSTATUS(status));
	if (!master->verbose)
		return ;
	if (WIFEXITED(status))
		printf("DEBUG terminé, code=%d\n", WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		printf("DEBUG tué par le signal %d\n", WTERMSIG(status));
	else if (WIFSTOPPED(status))
		printf("DEBUG arrêté par le signal %d\n", WSTOPSIG(status));
	else if (WIFCONTINUED(status))
		printf("DEBUG relancé\n");
}

static t_bool	ms_cmd_os_run_parent(t_master *master, pid_t cpid)
{
	pid_t	wpid;
	int		status;

	status = -1;
	while (status == -1 || (!WIFEXITED(status) && !WIFSIGNALED(status)))
	{
		wpid = waitpid(cpid, &status, WUNTRACED | WCONTINUED);
		if (wpid == -1)
		{
			perror("waitpid");
			exit(EXIT_FAILURE);
		}
		ms_cmd_os_run_parent_verbose(master, status);
	}
	return (TRUE);
}

t_bool	ms_cmd_os_run(t_master *master, char *command,
				char **argv, char **env)
{
	/*pid_t	cpid;

	cpid = fork();
	if (cpid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (cpid == 0)*/
		execve(command, argv, env);
/*	else
		ms_cmd_os_run_parent(master, cpid);*/
	return (TRUE);
}
