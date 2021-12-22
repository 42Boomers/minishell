/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: neben <neben@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 15:11:30 by ngeschwi          #+#    #+#             */
/*   Updated: 2021/11/29 13:34:57 by neben            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_already_here(t_shell *shell, char *value)
{
	int		i;
	int		j;
	int		check;
	char	**tab;

	tab = ft_split(value, '=');
	if (check_add(shell, (&tab)[0]) == SUCCESS)
		return (SUCCESS);
	i = get_current_env_int(shell, tab[0]);
	free_tab(tab);
	if (i == -1)
		return (ERROR);
	j = -1;
	check = 0;
	while (value[++j])
		if (value[j] == '=')
			check++;
	if (check)
	{
		free(shell->env[i]);
		shell->env[i] = ft_strdup(value);
	}
	return (SUCCESS);
}

static void	change_env(t_shell *shell, int i)
{
	char	**save_env;
	int		j;

	save_env = malloc(sizeof(char *) * (ft_tablen(shell->env) + 1));
	if (!save_env)
		return ;
	j = -1;
	while (shell->env[++j])
		save_env[j] = ft_strdup(shell->env[j]);
	save_env[j] = NULL;
	free_tab(shell->env);
	shell->env = malloc(sizeof(char *) * (ft_tablen(save_env) + 2));
	if (!save_env)
		return ;
	j = 0;
	while (save_env[j])
	{
		shell->env[j] = ft_strdup(save_env[j]);
		j++;
	}
	shell->env[j] = ft_strdup(shell->command_list->argv[i]);
	shell->env[j + 1] = NULL;
	free_tab(save_env);
}

static int	check_value(char *value)
{
	int	i;

	i = 0;
	while (value[i] && value[i] != '=')
	{
		if (!ft_isalnum(value[i]) && value[i] != '_' && value[i] != '+')
			return (0);
		i++;
	}
	return (1);
}

static int	do_redirection(t_shell *shell)
{
	if (shell->command_list->redirection_out == 2)
	{
		if (shell->pipe_fd[shell->index][0])
			close(shell->pipe_fd[shell->index][0]);
		if (dup2(shell->command_list->fd_out,
				shell->pipe_fd[shell->index][1]) == -1)
			ft_error_fork(shell, "Error, dup2");
	}
	else if (!shell->command_list->next)
	{
		if (shell->pipe_fd[shell->index][0])
			close(shell->pipe_fd[shell->index][0]);
		if (dup2(1, shell->pipe_fd[shell->index][1]) == -1)
			ft_error_fork(shell, "Error dup2 cmd");
	}
	return (-1);
}

int	ft_export(t_shell *shell)
{
	int	i;

	i = do_redirection(shell);
	if (shell->command_list->argv[1] == NULL
		|| ft_strlen(shell->command_list->argv[1]) == 0)
		while (shell->env[++i])
			printf("declare -x %s\n", shell->env[i]);
	else
	{
		i = 0;
		while (shell->command_list->argv[++i])
		{
			if (ft_isdigit(shell->command_list->argv[i][0]))
				printf("Error export not a valid identifier\n");
			if (!check_value(shell->command_list->argv[i]))
				printf("Error export not a valid identifier\n");
			else if (shell->command_list->argv[i][0] == '=')
				printf("Error export '=' not a valid identifier\n");
			else if (check_already_here(shell,
					shell->command_list->argv[i]) == ERROR)
				change_env(shell, i);
		}
	}
	send_env(shell);
	return (SUCCESS);
}
