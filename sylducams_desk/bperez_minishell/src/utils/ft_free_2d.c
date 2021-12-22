/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_free_2d.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: bperez <bperez@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/23 17:08:53 by bperez       #+#   ##    ##    #+#       */
/*   Updated: 2020/01/10 15:08:41 by bperez      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <stdlib.h>

void	ft_free_2d(void **array, size_t size)
{
	if (array)
	{
		while (size--)
		{
			if (array[size])
				free(array[size]);
		}
		free(array);
	}
}
