/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlepart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 17:44:04 by rlepart           #+#    #+#             */
/*   Updated: 2021/01/13 19:12:15 by rlepart          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1000

# endif

size_t		ft_strlen(const char *str);
int			ft_strichr(const char *str, char c);
char		*ft_strdup(const char *src);
char		*ft_str_join(char *s1, char *s2);
void		*ft_calloc(size_t count, size_t size);
char		*ft_substr(const char *s, unsigned int start, size_t len);
int			get_next_line(int fd, char **line);

#endif
