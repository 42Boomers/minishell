/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_build2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrozniec <mrozniec@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 02:00:47 by mrozniec          #+#    #+#             */
/*   Updated: 2021/12/16 16:49:09 by mrozniec         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_str_array_build(t_str_build *builder)
{
	char	**out;
	t_list	*tmp;

	tmp = builder->lst;
	out = malloc(sizeof(char *) * builder->lst_size);
	if (!out)
		return (NULL);
	while (tmp)
	{
		*out++ = ft_strdup(tmp->content);
	}
	return (out);
}

void	ft_str_destroy(t_str_build *builder)
{
	ft_lstclear(&builder->lst, free);
	if (builder->separator)
		free(builder->separator);
	free(builder);
}
