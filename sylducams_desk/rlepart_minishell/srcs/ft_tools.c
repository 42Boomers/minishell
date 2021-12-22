/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tools.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-kada <mel-kada@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 15:25:23 by rlepart           #+#    #+#             */
/*   Updated: 2021/03/03 21:32:37 by mel-kada         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_skip_spaces(char *str)
{
	while (*str && ft_isspace(*str))
		str++;
	return (str);
}

int		ft_no_bs(char *str, int i)
{
	int	count;

	count = 0;
	while (i > 0 && (str[i - 1] == '\\'))
	{
		count++;
		i--;
	}
	return ((count % 2) == 0);
}

int		ft_no_s_quote(char *str, int i)
{
	int	j;
	int	s;

	j = 0;
	s = 0;
	while (j < i)
	{
		s = (str[j] == '\'') + 2 * (str[j] == '"') * ft_no_bs(str, j);
		while (str[++j] && j < i && s != 0)
		{
			if (((str[j] == '\'') && (s == 1)) || ((str[j] == '"')
				&& (s == 2) && ft_no_bs(str, j)))
				s = 0;
		}
	}
	return (s != 1);
}

int		ft_no_d_quote(char *str, int i)
{
	int	j;
	int	d;

	j = 0;
	d = 0;
	while (j < i)
	{
		d = (str[j] == '\'') + 2 * (str[j] == '"') * ft_no_bs(str, j);
		while (str[++j] && j < i && d != 0)
		{
			if (((str[j] == '\'') && (d == 1)) || ((str[j] == '"')
				&& (d == 2) && ft_no_bs(str, j)))
				d = 0;
		}
	}
	return (d != 2);
}

int		ft_get_nbr_index(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}
