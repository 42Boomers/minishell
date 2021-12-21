/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tglory <tglory@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 21:49:56 by tglory            #+#    #+#             */
/*   Updated: 2021/12/21 02:20:50 by tglory           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_println_red(char *str)
{
	fprintf(stderr, "\e[31m%s.\e[0m\n", str);
}

void	ft_println_orange(char *str)
{
	printf("\e[208m%s.\e[0m\n", str);
}

void	ft_println(char *str)
{
	printf("%s.\n", str);
}
