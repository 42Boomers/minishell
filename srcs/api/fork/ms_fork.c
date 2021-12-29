/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_fork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblache <jblache@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 10:07:29 by jblache           #+#    #+#             */
/*   Updated: 2021/12/29 15:08:48 by jblache          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ms_child(t_master *master, char *command, char **args, int args_siz)
{
	t_ms_command	*cmd;
	t_ms_input		*input;

	cmd = ft_lstget(master->cmds, command, ms_cmd_get_key);
	if (cmd)
	{
		input = ms_cmd_input(cmd, args, args_siz);
		ms_set_status(master, ms_cmd_execute(input));
		ms_garbage_free(&input->garbage);
		free(input);
		exit(0);
	}
	else if (!ms_cmd_os(master, command, args))
		ms_print_cmd_not_found(master->name, command);
	exit(-1);
}

static int	ms_wait_fork(t_master *master, char **args, int *redir, int pip_rec)
{
	int	status;

	if (pip_rec > 0)
	{
		if (redir)
		{
			waitpid(master->pid, &status, 0);
			register_signal_main();
			master->last_status = WEXITSTATUS(status);
			if (redir[0] > 0)
				close(redir[0]);
			if (redir[1] > 0)
				close(redir[1]);
			free(redir);
		}
		pip_rec = ft_pipe_check(args);
	}
	else if (pip_rec == 0)
	{
		pip_rec = ft_pipe_check(args);
		if (pip_rec < 0)
			write(2, \
					"minishell: syntax error near unexpected token `|'\n", 50);
	}
	return (pip_rec);
}

static char	*ms_next_fork(int pip_rec, int pip_end[2], int *fd_in, char ***args)
{
	char	*command;

	close(pip_end[1]);
	if (*fd_in > 0)
		close(*fd_in);
	*fd_in = pip_end[0];
	command = (*args)[pip_rec];
	*args = &((*args)[pip_rec + 1]);
	ms_check_redir(&command, *args);
	return (command);
}

static int	*ms_fork_init(int *fd_in, int pip_end[2], char **args, \
	t_master *master)
{
	int	*redir;

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
	register_signal_fork();
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
	int	pip_end[2];
	int	fd_in;
	int	*redir;
	int	pip_rec;

	ft_init_ms_fork(&fd_in, &pip_rec);
	while (pip_rec > 0)
	{
		pip_rec = ft_red_pip_cmd(&command, args, master);
		if (pip_rec == -1)
			return ;
		if (pip_rec > 0 && ms_error_pipe(pip_end) == -1)
			return ;
		if (pip_rec > 0)
			redir = ms_fork_init(&fd_in, pip_end, args, master);
		if (pip_rec > 0 && master->pid == 0)
			ms_child(master, command, args, args_size);
		else
		{
			pip_rec = ms_wait_fork(master, args, redir, pip_rec);
			if (pip_rec > 0)
				command = ms_next_fork(pip_rec, pip_end, &fd_in, &args);
		}
	}
	ms_fork_free(fd_in, pip_end[0], pip_end[1]);
}
