/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_fork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tglory <tglory@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 10:07:29 by tglory            #+#    #+#             */
/*   Updated: 2021/12/22 23:14:23 by tglory           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ms_child(t_master *master, char *command, char **args, int args_siz)
{
	char	*error;
	t_ms_command	*cmd;
	t_ms_input		*input;

	pid = getpid();								// to delete
	dprintf(1, "ms_fork.c:20 pid = %d\n", pid); // to delete
	if (ft_isequals(command, "exit"))
		exit(0);
	cmd = ft_lstget(master->cmds, command, ms_cmd_get_key);
	if (cmd)
	{
		input = ms_cmd_input(cmd, args, args_siz);
		ms_set_status(master, ms_cmd_execute(input));
		free(args);
		ms_garbage_free(&input->garbage);
		free(input);
		exit(0);
	}
	else if (!ms_cmd_os(master, command, args))
	{
		error = ft_strjoin("minishell: ", command);
		perror(error);
		free(error);
		exit(127);
	}
	exit(-1);
}

static int ms_wait_fork(t_master *master, char **args, int *redir)
{
	int status;

	if (redir)
	{
		waitpid(master->pid, &status, 0);
		printf("last_status %d\n", WIFEXITED(status));
		master->last_status = WIFEXITED(status);
		pid = getpid();								// to delete
		// dprintf(1, "ms_fork.c:43 pid = %d\n", pid); // to delete
		if (redir[0] > 0)
			close(redir[0]);
		if (redir[1] > 0)
			close(redir[1]);
		free(redir);
	}
	return (ft_pipe_check(args));
}

static char *ms_next_fork(int pip_rec, int pip_end[2], int *fd_in, char ***args)
{
	char *command;

	close(pip_end[1]);
	*fd_in = pip_end[0];
	command = (*args)[pip_rec];
	*args = &((*args)[pip_rec + 1]);
	ms_check_redir(&command, *args);
	return (command);
}

static int *ms_fork_init(int *fd_in, int pip_end[2], char **args, t_master *master)
{
	int *redir;

	redir = malloc(2 * sizeof(int));
	if (!redir)
	{
		ft_println_red("Error > An error has occured while malloc creation");
		return (NULL);
	}
	if (ms_red_in_out(args, redir))
	{
		free(redir);
		return (NULL);
	}
	master->pid = fork();
	if (master->pid < 0)
	{
		ft_println_red("Error > An error has occured while fork creation");
		return (NULL);
	}
	if (master->pid == 0)
		ms_fork_init2(args, redir, pip_end, fd_in);
	return (redir);
}

void	ms_fork(t_master *master, char *command, char **args, int args_size)
{
	int pip_end[2];
	int fd_in;
	int *redir;
	int pip_rec;

	pip_rec = 1;
	while (pip_rec > 0)
	{
		if (ms_error_pipe(pip_end) == -1)
			return;
		redir = ms_fork_init(&fd_in, pip_end, args, master);
		if (master->pid == 0)
			ms_child(master, command, args, args_size);
		else
		{
			pip_rec = ms_wait_fork(master, args, redir);
			if (pip_rec < 0)
				write(2, \
				"minishell: syntax error near unexpected token `|'\n", 50);
			if (pip_rec > 0)
				command = ms_next_fork(pip_rec, pip_end, &fd_in, &args);
		}
	}
}
