/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_build.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tglory <tglory@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 02:00:47 by tglory            #+#    #+#             */
/*   Updated: 2021/12/16 16:51:52 by tglory           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_str_build	*ft_str_build_init(void)
{
	t_str_build	*builder;

	builder = malloc(sizeof(*builder));
	if (!builder)
		return (NULL);
	builder->char_size = 0;
	builder->lst_size = 0;
	builder->lst = NULL;
	builder->separator = NULL;
	return (builder);
}

void	ft_str_add(t_str_build *builder, char *str)
{
	builder->char_size += ft_strlen(str);
	builder->lst_size++;
	ft_lstadd_back(&(builder->lst), ft_lstnew(str));
}

void	ft_strfill(size_t i, char *dest, const char *src)
{
	int	index;

	index = 0;
	while (src[index])
		dest[i++] = src[index++];
	dest[i] = 0;
}

static void	ft_lst_to_str(t_str_build *builder, char **out)
{
	int		i;
	t_list	*tmp;

	i = 0;
	tmp = builder->lst;
	while (tmp)
	{
		ft_strfill(i, *out, tmp->content);
		i += ft_strlen(tmp->content);
		tmp = tmp->next;
		if (builder->separator && !tmp)
			ft_strcpy(*out, builder->separator);
	}
}

char	*ft_str_build(t_str_build *builder)
{
	char	*out;
	int		size;

	size = builder->char_size;
	if (builder->separator)
		size += ft_strlen(builder->separator)
			* (builder->lst_size - 1);
	out = malloc(sizeof(char) * (size + 1));
	if (!out)
		return (NULL);
	ft_lst_to_str(builder, &out);
	return (out);
}
