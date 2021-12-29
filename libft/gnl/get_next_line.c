/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tglory <tglory@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 12:15:27 by tglory            #+#    #+#             */
/*   Updated: 2021/12/02 17:56:10 by tglory           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_contains_eol(char *str)
{
	int	i;

	i = -1;
	if (!str)
		return (0);
	while (str[++i])
		if (str[i] == '\n')
			return (1);
	return (0);
}

char	*ft_create_line(char *s)
{
	int		i;
	char	*str;

	i = -1;
	while (s[++i] && s[i] != '\n')
		;
	str = malloc(sizeof(char) * (i + 1));
	if (!str)
		return (NULL);
	i = -1;
	while (s[++i] && s[i] != '\n')
		str[i] = s[i];
	str[i] = 0;
	return (str);
}

char	*ft_get_after_eol(char *save)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	while (save[i] && save[i] != '\n')
		i++;
	if (!(save[i]))
	{
		free(save);
		return (NULL);
	}
	str = malloc(sizeof(char) * (ft_strlen(save) - i + 1));
	if (!str)
	{
		free(save);
		return (NULL);
	}
	i++;
	while (save[i])
		str[j++] = save[i++];
	str[j] = 0;
	free(save);
	return (str);
}

int	ft_create_and_save(char **save, char **line, int size)
{
	*line = ft_create_line(*save);
	*save = ft_get_after_eol(*save);
	if (size <= 0)
	{
		free(*save);
		return (0);
	}
	return (1);
}

int	get_next_line(int fd, char **line)
{
	char				buf[BUFFER_SIZE + 1];
	static char			*save[4096];
	int					size;

	if (!line || fd < 0 || BUFFER_SIZE <= 0)
		return (-1);
	size = 1;
	if (!save[fd])
		save[fd] = ft_strdup("");
	while (!(ft_contains_eol(save[fd])))
	{
		size = read(fd, buf, BUFFER_SIZE);
		if (size == -1)
			return (-1);
		else if (size == 0)
			break ;
		buf[size] = 0;
		save[fd] = ft_strjoin_gnl(save[fd], buf, 1);
	}
	return (ft_create_and_save(&save[fd], line, size));
}
