/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_env_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngeschwi <nathan.geschwind@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 17:09:12 by ngeschwi          #+#    #+#             */
/*   Updated: 2021/11/25 12:06:35 by ngeschwi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	send_env(t_shell *shell)
{
	char	*chaine_env;
	int		i;
	int		size;

	i = -1;
	size = 0;
	while (shell->env[++i])
		size += ft_strlen(shell->env[i]) + 1;
	chaine_env = malloc(sizeof(char) * (size + 1));
	if (!chaine_env)
		return ;
	i = 0;
	chaine_env = ft_strdup(shell->env[i]);
	chaine_env = ft_strjoin(chaine_env, "\n");
	while (shell->env[++i])
	{
		chaine_env = ft_strjoin(chaine_env, shell->env[i]);
		chaine_env = ft_strjoin(chaine_env, "\n");
	}
	chaine_env[size] = '\0';
	if (shell->pipe_export[0])
		close(shell->pipe_export[0]);
	write(shell->pipe_export[1], chaine_env, size);
	if (shell->pipe_export[1])
		close(shell->pipe_export[1]);
}
