/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngeschwi <nathan.geschwind@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 16:12:23 by ngeschwi          #+#    #+#             */
/*   Updated: 2021/11/25 17:05:19 by ngeschwi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*copy_tab(char *tab)
{
	int		i;
	char	*new_tab;

	i = 0;
	while (tab[i] && tab[i] != '+')
		i++;
	new_tab = malloc(sizeof(char) * (i + 1));
	i = 0;
	while (tab[i] && tab[i] != '+')
	{
		new_tab[i] = tab[i];
		i++;
	}
	new_tab[i] = '\0';
	return (new_tab);
}

static char	*ft_strcat(char *str1, char *str2)
{
	int		i;
	int		j;
	char	*cat;

	i = 0;
	j = 0;
	cat = malloc(sizeof(char) * (ft_strlen(str1) + ft_strlen(str2) + 1));
	while (str1[i])
	{
		cat[j] = str1[i];
		i++;
		j++;
	}
	i = 0;
	while (str2[i])
	{
		cat[j] = str2[i];
		i++;
		j++;
	}
	cat[j] = '\0';
	return (cat);
}

static void	change_env_export_add(t_shell *shell, char *tab)
{
	char	**save_env;
	char	**split;
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
	j = -1;
	while (save_env[++j])
		shell->env[j] = ft_strdup(save_env[j]);
	split = ft_split(shell->command_list->argv[1], '+');
	shell->env[j] = ft_strdup(tab);
	shell->env[j] = ft_strjoin(shell->env[j], split[1]);
	shell->env[j + 1] = NULL;
	free_tab(save_env);
	free_tab(split);
}

static void	check_here(t_shell *shell, char **tab)
{
	int		i;
	char	**split;
	char	*shell_i;

	i = get_current_env_int(shell, *tab);
	if (i == -1)
		change_env_export_add(shell, *tab);
	else
	{
		shell_i = ft_strdup(shell->env[i]);
		free(shell->env[i]);
		split = ft_split(shell->command_list->argv[1], '=');
		shell->env[i] = ft_strcat(shell_i, split[1]);
		free_tab(split);
	}
}

int	check_add(t_shell *shell, char **tab)
{
	char	*save_tab;

	if ((*tab)[ft_strlen(*tab) - 1] == '+')
	{
		save_tab = ft_strdup(*tab);
		free(*tab);
		*tab = copy_tab(save_tab);
		check_here(shell, tab);
		return (SUCCESS);
	}
	return (ERROR);
}
