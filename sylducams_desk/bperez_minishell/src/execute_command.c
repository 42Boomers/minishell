/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: neben <neben@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 18:27:34 by ngeschwi          #+#    #+#             */
/*   Updated: 2021/11/29 13:33:26 by neben            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	care_pipe(t_shell *shell)
{
	if (shell->index == 2)
		shell->index = 0;
	else
		shell->index++;
	if (shell->index == 2)
	{
		if (shell->pipe_fd[0][0])
			close(shell->pipe_fd[0][0]);
		if (shell->pipe_fd[0][0])
			close(shell->pipe_fd[0][1]);
		if (pipe(shell->pipe_fd[0]) == -1)
			perror("Error pipe initialisation");
	}
	else
	{
		if (shell->pipe_fd[shell->index + 1][0])
			close(shell->pipe_fd[shell->index + 1][0]);
		if (shell->pipe_fd[shell->index + 1][1])
			close(shell->pipe_fd[shell->index + 1][1]);
		if (pipe(shell->pipe_fd[shell->index + 1]) == -1)
			perror("Error pipe initialisation");
	}
}

static void	get_env_export(t_shell *shell)
{
	int		ret;
	char	buff[1024 + 1];
	char	*str;

	str = NULL;
	if (shell->pipe_export[1])
		close(shell->pipe_export[1]);
	ret = read(shell->pipe_export[0], buff, 1024);
	buff[ret] = '\0';
	while (ret > 0)
	{
		str = ft_strjoin(str, buff);
		ret = read(shell->pipe_export[0], buff, 1024);
		buff[ret] = '\0';
	}
	if (shell->pipe_export[0])
		close(shell->pipe_export[0]);
	free_tab(shell->env);
	shell->env = ft_split(str, '\n');
}

static void	close_pipe_after_cmd(t_shell *shell)
{
	if (shell->index == 0)
	{
		if (shell->pipe_fd[2][0])
			close(shell->pipe_fd[2][0]);
		if (shell->pipe_fd[2][1])
			close(shell->pipe_fd[2][1]);
	}
	else
	{
		if (shell->pipe_fd[shell->index - 1][0])
			close(shell->pipe_fd[shell->index - 1][0]);
		if (shell->pipe_fd[shell->index - 1][1])
			close(shell->pipe_fd[shell->index - 1][1]);
	}
}

static void	check_exit_siganls(t_shell *shell, int status)
{
	if (status == EXIT_CMD * ERRNO_DEFAULT_VALUE)
		status = ERRNO_DEFAULT_VALUE;
	if (WIFSIGNALED(status) == 1)
		shell->last_exit_status = status + 128;
	else
		shell->last_exit_status = status / ERRNO_DEFAULT_VALUE;
	g_process_section = 0;
	care_pipe(shell);
	if (shell->command_list->redirection_in == REDIRECTION_DINPUT)
		close_pipe_rdi(shell);
	if (shell->command_list->argv[0])
		if (!ft_strcmp(shell->command_list->argv[0], "export"))
			get_env_export(shell);
}

void	execute_command(t_shell *shell)
{
	pid_t	pid;
	int		status;

	status = check_commad_1(shell) * ERRNO_DEFAULT_VALUE;
	if (status == ERROR * ERRNO_DEFAULT_VALUE)
	{
		g_process_section = 1;
		if (shell->command_list->redirection_in == REDIRECTION_DINPUT)
			exec_cmd_for_rdi(shell);
		pid = fork();
		if (pid == -1)
			ft_error_fork(shell, "Error fork() execute_command");
		else if (pid == 0)
			do_redirection_in(shell);
		else
		{
			close_pipe_after_cmd(shell);
			waitpid(-1, &status, 0);
			shell->last_exit_status = status / 256;
		}
	}
	check_exit_siganls(shell, status);
	do_after_cmd(shell);
}
