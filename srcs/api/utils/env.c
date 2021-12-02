/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tglory <tglory@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 18:10:36 by tglory            #+#    #+#             */
/*   Updated: 2021/12/02 19:12:05 by tglory           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_env_get(char *env)
{
	char	**env_array = ft_split(env, '=');
	if (!env_array[0])
	{
		free(env_array);
		return (NULL);
	}
	return (env_array);
}

static int	ft_env_print(char *key, char *value)
{
	return (printf("%s=%s\n", key, value));
}

void	ft_env_print_all(char **envs)
{
	char **e;

	while (*envs)
	{
		e = ft_env_get(*envs++); // Need more check here
		if (!e || !e[0] || !e[1])
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
