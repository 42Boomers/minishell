/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_pwd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngeschwi <nathan.geschwind@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 12:37:38 by ngeschwi          #+#    #+#             */
/*   Updated: 2021/11/25 09:39:25 by ngeschwi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	order_pwd(char **save_pwd, int check, int i)
{
	int		new_size;
	int		j;
	int		k;
	char	*new_pwd;

	j = 0;
	k = 0;
	new_size = ft_strlen(*save_pwd) - (check - i);
	new_pwd = malloc(sizeof(char) * (new_size + 1));
	if (new_pwd)
	{
		while ((*save_pwd)[j])
		{
			new_pwd[k] = (*save_pwd)[j];
			j++;
			k++;
			if (j == i)
				j = check;
		}
		new_pwd[k] = '\0';
		free(*save_pwd);
		*save_pwd = ft_strdup(new_pwd);
		free(new_pwd);
	}
}

void	check_pwd(t_shell *shell)
{
	int		i;
	int		check;
	char	*save_pwd;

	i = get_current_env_int(shell, "PWD");
	save_pwd = ft_strdup(shell->env[i]);
	i = 0;
	check = 0;
	while (save_pwd[i])
	{
		if (save_pwd[i] == '.' && save_pwd[i + 1] && save_pwd[i + 1] == '.')
		{
			check = i + 2;
			i = i - 2;
			while (save_pwd[i] && save_pwd[i] != '/')
				i--;
			order_pwd(&save_pwd, check, i);
		}
		i++;
	}
	i = get_current_env_int(shell, "PWD");
	free(shell->env[i]);
	shell->env[i] = ft_strdup(save_pwd);
	free(save_pwd);
}
