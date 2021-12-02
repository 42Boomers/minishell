/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tglory <tglory@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 02:18:10 by tglory            #+#    #+#             */
/*   Updated: 2021/12/02 17:40:39 by tglory           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	read_env(char *env)
{

}


int	main(int av, char **ag, char **env)
{
	(void)av;
	(void)ag;
	(void)env;
	while (*env)
		printf("DEBUG %s\n", *env++);
	return (0);
}
