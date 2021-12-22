/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlepart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 16:21:30 by rlepart           #+#    #+#             */
/*   Updated: 2021/01/16 16:21:32 by rlepart          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	int		j;
	char	ch;
	char	*str;

	str = (char *)s;
	i = 0;
	j = -1;
	ch = c;
	while (str[i])
	{
		if (str[i] == ch)
			j = i;
		i++;
	}
	if (str[i] == ch)
		j = i;
	if (j == -1)
		return (0);
	return (str + j);
}
