/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tglory <tglory@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 18:10:36 by tglory            #+#    #+#             */
/*   Updated: 2021/12/03 20:18:40 by tglory           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_env_print(char *key, char *value)
{
	return (printf("%s=%s\n", key, value));
}

void	ft_env_print_all(char **envs)
{
	char	**e;

	while (*envs)
	{
		e = ft_strtrunc(*envs++, '=');
		if (!e)
			continue ;
		ft_env_print(e[0], e[1]);
		free(e[0]);
		free(e[1]);
		free(e);
	}
}

void	set_env(char *key, char *value)
{
	(void)key;
	(void)value;
}
