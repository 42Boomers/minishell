/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlepart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 16:18:42 by rlepart           #+#    #+#             */
/*   Updated: 2021/01/16 16:18:44 by rlepart          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static long	ft_pow(int n, int pow)
{
	long	nb;

	nb = 1;
	while (pow > 0)
	{
		nb = nb * (long)n;
		pow--;
	}
	return (nb);
}

char		*ft_itoa(int n)
{
	char	*str;
	int		nb;
	int		i;

	nb = n;
	i = ((n <= 0) ? 2 : 1);
	while (nb != 0 && ((nb = nb / 10) == 0 || 1))
		i++;
	if (!(str = ft_calloc(i, sizeof(*str))))
		return (0);
	i--;
	while (nb < i)
		str[nb++] = '0';
	str[0] = ((n < 0) ? '-' : '0');
	nb = 1;
	while (i - nb >= 0 && str[i - nb] != '-')
	{
		while ((long)ft_atoi(str) % ft_pow(10, nb) != (long)n % ft_pow(10, nb))
		{
			str[i - nb]++;
		}
		nb++;
	}
	return (str);
}
