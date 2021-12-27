/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tglory <tglory@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 17:52:40 by tglory            #+#    #+#             */
/*   Updated: 2021/12/02 17:57:52 by tglory           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count(long n)
{
	long	i;

	i = 0;
	if (n == 0)
		return (1);
	while (n)
	{
		n /= 10;
		i++;
	}
	return (i);
}

static char	*ft_cpyword(char *s, long nb, long len)
{
	if (nb == 0)
	{
		s[0] = '0';
		return (s);
	}
	while (nb)
	{
		s[len] = nb % 10 + '0';
		nb /= 10;
		len--;
	}
	return (s);
}

char	*ft_itoa(long n)
{
	char	*str;
	int		neg;
	int		len;
	long	haine;

	neg = 0;
	haine = (long)n;
	if (haine < 0)
	{
		neg = 1;
		haine = -1 * haine;
	}
	len = ft_count(haine) + neg;
	str = malloc(sizeof(char) * (len + 1));
	if (!(str))
		return (NULL);
	str[len] = 0;
	ft_cpyword(str, haine, (len - 1));
	if (neg == 1)
		str[0] = '-';
	return (str);
}
