/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_parse_struct.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tglory <tglory@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 03:40:32 by tglory            #+#    #+#             */
/*   Updated: 2021/12/20 03:40:53 by tglory           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env_parse	*ms_env_parse_create(t_master *master, char *str)
{
	t_env_parse		*env_parse;

	env_parse = malloc(sizeof(*env_parse));
	if (!env_parse)
		return (NULL);
	env_parse->master = master;
	env_parse->build = NULL;
	env_parse->str = str;
	env_parse->str2 = str;
	env_parse->out = NULL;
	env_parse->i = 0;
	env_parse->k = -1;
	return (env_parse);
}
