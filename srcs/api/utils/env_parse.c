/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tglory <tglory@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 02:35:52 by tglory            #+#    #+#             */
/*   Updated: 2021/12/27 22:46:28 by tglory           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ms_env_parse_out(t_env_parse *ep)
{
	char	*tmp;

	tmp = ft_strdup(ep->out);
	if (ep->build)
		ft_str_destroy(ep->build);
	free(ep->out);
	free(ep);
	return (tmp);
}

static char	*ms_env_parse_str_check(t_env_parse *ep)
{
	if (!ep->out)
	{
		ft_str_destroy(ep->build);
		return (NULL);
	}
	return (ms_env_parse_out(ep));
}

static char	*ms_env_parse_build(t_env_parse *ep)
{
	char	*tmp;

	tmp = NULL;
	if (ep->build)
	{
		tmp = ft_str_build(ep->build);
		ft_str_destroy(ep->build);
	}
	free(ep);
	return (tmp);
}

char	*ms_env_parse(t_master *master, char *str)
{
	t_env_parse	*ep;

	ep = ms_env_parse_create(master, str);
	while (*(ep->str))
	{
		if (!*(ep->str) || !(ep->str + 1))
			break ;
		if (!ms_env_parse_search(ep))
		{
			if (!ep->build && ep->out)
				return (ms_env_parse_out(ep));
			continue ;
		}
		if (!ms_env_parse_str(ep))
			return (ms_env_parse_str_check(ep));
		if (!*ep->str || !(*ep->str + 1))
			break ;
		if (*(ep->str) == '$')
		{
			ep->i++;
			(ep->str)++;
		}
		if (ep->str && !ms_env_parse_var(ep))
			return (NULL);
		ep->str2 = (ep->str);
		ep->k = ep->i++;
	}
	return (ms_env_parse_build(ep));
}
