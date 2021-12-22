/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: bperez <bperez@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/15 19:28:42 by bperez       #+#   ##    ##    #+#       */
/*   Updated: 2021/11/24 17:02:36 by bperez           ###   ########lyon.fr   */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "minishell.h"

static short	count_chars(int n)
{
	short	len;

	len = 1;
	while ((n / 10))
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(const int n)
{
	char			*str;
	unsigned int	n2;
	short			len;
	short			neg;

	len = count_chars(n);
	n2 = (unsigned int)n;
	if (n < 0)
		n2 = -(unsigned int)n;
	neg = n < 0;
	str = (char *)ft_calloc(len + neg + 1, sizeof(char));
	if (str)
	{
		while (len--)
		{
			str[len + neg] = n2 % 10 + '0';
			n2 /= 10;
		}
		if (neg)
			*str = '-';
	}
	return (str);
}
