/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_fork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sylducam <sylducam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 10:07:29 by tglory            #+#    #+#             */
/*   Updated: 2021/12/23 14:29:33 by sylducam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ms_child(t_master *master, char *command, char **args, int args_siz)
{
	t_ms_command	*cmd;
	t_ms_input		*input;

	if (ft_isequals(command, "exit"))
		exit(0);
	cmd = ft_lstget(master->cmds, command, ms_cmd_get_key);
	if (cmd)
	{
		input = ms_cmd_input(cmd, args, args_siz);
		// ms_set_status didnt work cause it is override by fork result
		// We won't need to use fork at this case.
		ms_set_status(master, ms_cmd_execute(input));
		free(args);
		ms_garbage_free(&input->garbage);
		free(input);
		exit(0);
	}
	else if (!ms_cmd_os(master, command, args))
	{
		// ms_set_status(master, FALSE);
		master->last_status = 127;
		if (errno == ENOENT)
			fprintf(stderr, "%s: %s: command not found\n",
				master->name, command);
		else
			ms_print_error(master->name, command);
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
		master->last_status = WEXITSTATUS(status);
		//printf("FORK last_status %d\n", WEXITSTATUS(status));
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
		pip_rec = ft_red_pip_cmd(&command, args);
		if (pip_rec > 0 && ms_error_pipe(pip_end) == -1)
			return;
		if (pip_rec > 0)
			redir = ms_fork_init(&fd_in, pip_end, args, master);
		if (pip_rec > 0 && master->pid == 0)
			ms_child(master, command, args, args_size);
		else
		{
			if (pip_rec > 0)
				pip_rec = ms_wait_fork(master, args, redir);
			else if (pip_rec == 0)
			{
				pip_rec = ft_pipe_check(args);
				if (pip_rec < 0)
					write(2, \
					"minishell: syntax error near unexpected token `|'\n", 50);
			}
			if (pip_rec > 0)
				command = ms_next_fork(pip_rec, pip_end, &fd_in, &args);
		}
	}
}
