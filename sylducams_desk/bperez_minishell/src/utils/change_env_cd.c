/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_env_cd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngeschwi <nathan.geschwind@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 17:05:30 by ngeschwi          #+#    #+#             */
/*   Updated: 2021/11/25 15:54:47 by ngeschwi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	change_env_cd(t_shell *shell)
{
	int		i;
	char	*save_pwd;

	i = get_current_env_int(shell, "PWD");
	if (i == -1)
		return (EXIT_CMD);
	save_pwd = ft_strdup(shell->env[i]);
	free(shell->env[i]);
	shell->env[i] = NULL;
	shell->env[i] = ft_strdup("PWD=");
	shell->env[i] = ft_strjoin(shell->env[i], shell->command_list->argv[1]);
	check_pwd(shell);
	i = get_current_env_int(shell, "OLDPWD");
	if (i == -1)
		return (EXIT_CMD);
	free(shell->env[i]);
	shell->env[i] = NULL;
	shell->env[i] = ft_strdup("OLD");
	shell->env[i] = ft_strjoin(shell->env[i], save_pwd);
	free(save_pwd);
	return (SUCCESS);
}
