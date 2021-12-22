/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlepart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 16:20:40 by rlepart           #+#    #+#             */
/*   Updated: 2021/01/16 16:20:42 by rlepart          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strchr(const char *s, int c)
{
	char	ch;
	char	*str;
	int		i;

	ch = c;
	i = -1;
	str = (char *)s;
	while (str[++i])
		if (str[i] == ch)
			return (str + i);
	if (str[i] == ch)
		return (str + i);
	return (0);
}
