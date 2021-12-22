/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_edit_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-kada <mel-kada@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 15:44:45 by rlepart           #+#    #+#             */
/*   Updated: 2021/03/11 21:33:53 by mel-kada         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_trim_cmd(char *str, int *tab)
{
	int		i;

	i = 0;
	while (tab[i] != -1)
	{
		str = ft_trim(str, tab[i] - i, tab[i] + 1 - i);
		i++;
	}
	return (str);
}

char	*ft_remove_bs_q(char *str)
{
	int		i;
	int		j;
	int		tab[100];

	i = 0;
	j = 100;
	while (--j >= 0)
		tab[j] = -1;
	j++;
	while (str && str[i])
	{
		if ((str[i] == '\\' && ((ft_no_s_quote(str, i) && ft_no_bs(str, i) &&
						(ft_no_d_quote(str, i) || str[i + 1] == '\\' ||
						str[i + 1] == '"')))) ||
				(str[i] == '\'' && (!ft_no_s_quote(str, i) ||
						(ft_no_d_quote(str, i) && ft_no_bs(str, i)))) ||
				(str[i] == '"' && ft_no_s_quote(str, i) && ft_no_bs(str, i)))
		{
			tab[j] = i;
			j++;
		}
		i++;
	}
	return (ft_trim_cmd(str, tab));
}

void	ft_split_cmd(t_content *content, char *buf)
{
	int		x;
	char	**list;
	char	**list_pipe;

	list = ft_split_args(buf, ';');
	x = 0;
	while (list[x])
	{
		if (!ft_check_quotes(list[x]) || !ft_check_redir(list[x], -1)
			|| !ft_check_pipe(list[x]))
			break ;
		list_pipe = ft_split_args(list[x], '|');
		if (ft_get_nbr_index(list_pipe) > 1)
			ft_process(content, list_pipe);
		else
		{
			if (ft_redir_parse(content, &(list[x])) != -1)
				ft_pars(content, ft_split_spaces(
					ft_get_var(content, list[x])), 0);
		}
		ft_free_tab(list_pipe);
		x++;
	}
	free(list);
}

char	*ft_get_var(t_content *content, char *buf)
{
	char	*s[2];
	int		i[2];

	s[0] = ft_strdup(buf);
	i[0] = -1;
	while (s[0] && s[0][++i[0]])
		if (s[0][i[0]] == '$' && s[0][i[0] + 1] != '?' &&
				ft_no_bs(s[0], i[0]) && ft_no_s_quote(s[0], i[0]))
		{
			i[1] = 1;
			while ((s[0][i[0] + i[1]] && ft_isalnum(s[0][i[0] + i[1]]))
					|| s[0][i[0] + i[1]] == '_')
				i[1]++;
			if (i[1] != 1 || s[0][i[0] + i[1]])
			{
				s[1] = ft_substr(s[0], i[0] + 1, i[1] - 1);
				s[0] = ft_insert(ft_trim(s[0], i[0], i[0] + i[1]), i[0],
						ft_get_env(content, s[1]));
				if (s[1])
					free(s[1]);
			}
		}
	free(buf);
	return (ft_replace_errno(s[0]));
}

char	*ft_replace_errno(char *str)
{
	int		i;
	char	*tmp;

	i = 0;
	while (str && str[i])
	{
		if (ft_no_bs(str, i) && str[i] == '$' && str[i + 1] == '?' &&
				ft_no_s_quote(str, i))
		{
			tmp = ft_itoa(errno);
			str = ft_insert(ft_trim(str, i, i + 2), i, tmp);
			if (tmp)
				free(tmp);
		}
		i++;
	}
	return (str);
}
