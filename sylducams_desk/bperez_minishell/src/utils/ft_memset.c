/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_memset.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: bperez <bperez@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/07 12:26:22 by bperez       #+#   ##    ##    #+#       */
/*   Updated: 2020/02/23 17:48:22 by bperez           ###   ########lyon.fr   */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memset(void *ptr, const unsigned int c, size_t len)
{
	while (len--)
		*((unsigned char *)ptr + len) = (unsigned char)c;
	return (ptr);
}
