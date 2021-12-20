/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_parse2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tglory <tglory@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 02:35:52 by tglory            #+#    #+#             */
/*   Updated: 2021/12/20 07:29:14 by tglory           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_bool	ms_env_parse_exit_status(t_env_parse *ep)
{
	if (!ep->str || !(ep->str) || *(ep->str) != '?')
		return (FALSE);
	(ep->str)++;
	ep->i++;
	ft_str_add(ep->build, ft_itoa(ep->master->last_status));
	return (TRUE);
}

t_bool	ms_env_parse_var(t_env_parse *ep)
{
	int		j;
	char	*tmp;
	char	*env;
	int		l;

	j = ep->i - 1;
	if (ms_env_parse_exit_status(ep))
		return (TRUE);
	while (*(ep->str) && (ft_isalnum(*(ep->str)) || *(ep->str) == '_'))
	{
		(ep->str)++;
		ep->i++;
	}
	tmp = ms_mallocw(sizeof(char) * (ep->i - j), "Error > cannot malloc");
	if (!tmp)
		return (FALSE);
	l = 0;
	while (ep->i - 1 > j)
		tmp[l++] = ep->str2[++j - (ep->k + 1)];
	tmp[l] = 0;
	env = ms_env_get(ep->master, tmp);
	free(tmp);
	if (env)
		ft_str_add(ep->build, ft_strdup(env));
	return (TRUE);
}

t_bool	ms_env_parse_search(t_env_parse *ep)
{
	if (*(ep->str) == '$' && !(*((ep->str) + 1)))
	{
		if (!ep->build)
			ep->out = ft_strdup("$");
		else
			ft_str_add(ep->build, ft_strdup("$"));
		return (FALSE);
	}
	while (*(ep->str) && *(ep->str) != '$')
	{
		ep->i++;
		(ep->str)++;
	}
	return (TRUE);
}

t_bool	ms_env_parse_str(t_env_parse *ep)
{
	if (ep->i == 0 && !*(ep->str))
	{
		ep->out = ft_strdup((ep->str));
		return (FALSE);
	}
	if (!ep->build)
		ep->build = ft_str_build_init();
	// if (*(ep->str) == '$' && !*(ep->str + 1))
	// {
	// 	ep->i++;
	// }
	if (ep->i != 0)
	{
		ep->tmp = malloc(sizeof(char) * (ep->i - ep->k));
		if (!ep->tmp)
		{
			ep->tmp = ft_itoa(ep->i - ep->k);
			ep->out = ft_strjoin("Error > Can't malloc of size ", ep->tmp);
			free(ep->tmp);
			ft_println_red(ep->out);
			free(ep->out);
			ep->out = NULL;
			return (FALSE);
		}
		ft_strlcpy(ep->tmp, ep->str2, ep->i - ep->k);
		ft_str_add(ep->build, ep->tmp);
	}
	return (TRUE);
}
