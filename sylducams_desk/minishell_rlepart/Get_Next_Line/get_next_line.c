/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlepart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 17:44:42 by rlepart           #+#    #+#             */
/*   Updated: 2021/02/17 17:50:02 by rlepart          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_str_join(char *str1, char *str2)
{
	size_t	ind;
	size_t	len;
	size_t	i;
	char	*concat;

	i = -1;
	ind = -1;
	len = ft_strlen(str1);
	if (str1 == 0 || !(concat =
				malloc(sizeof(*concat) * (len + ft_strlen(str2) + 1))))
		return (NULL);
	while (++i < len)
		concat[i] = str1[i];
	while (str2[++ind])
		concat[i + ind] = str2[ind];
	concat[i + ind] = '\0';
	free(str1);
	return (concat);
}

int		cut_line(char **save, int back_n, char **line)
{
	char *temp;

	if (back_n < 0)
	{
		*line = ft_strdup(*save);
		free(*save);
		*save = NULL;
		return (0);
	}
	*line = ft_substr(*save, 0, back_n);
	temp = ft_substr(*save, back_n + 1, ft_strlen(*save + back_n + 1));
	free(*save);
	*save = temp;
	if (*save[0] == '\0')
	{
		free(*save);
		*save = NULL;
	}
	return (1);
}

int		get_next_line(int fd, char **line)
{
	char		buffer[BUFFER_SIZE + 1];
	static char *save[20000];
	int			ret;
	int			back_n;

	if (fd < 0 || BUFFER_SIZE < 1 || !line || read(fd, buffer, 0) < 0 ||
			(!save[fd] && !(save[fd] = ft_calloc(1, sizeof(char)))))
		return (-1);
	while ((back_n = ft_strichr(save[fd], '\n')) < 0 &&
			(ret = read(fd, buffer, BUFFER_SIZE)) > 0)
	{
		buffer[ret] = '\0';
		save[fd] = ft_str_join(save[fd], buffer);
	}
	return (cut_line(&save[fd], back_n, line));
}
