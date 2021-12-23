/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tglory <tglory@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 21:49:56 by tglory            #+#    #+#             */
/*   Updated: 2021/12/24 00:48:13 by tglory           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_println_red(char *str)
{
	ft_putstr_fd("\e[31m", 2);
	ft_putstr_fd(str, 2);
	ft_putendl_fd(".\e[0m", 2);
}

void	ft_println_orange(char *str)
{
	printf("\e[208m%s.\e[0m\n", str);
}

void	ft_println(char *str)
{
	printf("%s.\n", str);
}
