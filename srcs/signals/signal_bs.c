/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tglory <tglory@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 03:26:27 by tglory            #+#    #+#             */
/*   Updated: 2021/12/24 04:47:04 by tglory           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static struct termios *old_termios;
static struct termios *new_termios;


void ctrl_bs_register(void)
{
	if (!new_termios)
	{
		printf("Register new termios\n");
		old_termios = malloc(sizeof(*old_termios));
		new_termios = malloc(sizeof(*new_termios));
		tcgetattr(0, old_termios);
		ft_memcpy(new_termios, old_termios, sizeof(*old_termios));
		// new_termios->c_cc[VEOF] = 3;	 // 3 = ^C
		// new_termios->c_cc[VINTR] = 4; // 4 = ^D
		// new_termios->c_cc[VKILL] = 34; // 34 = ^/
		// new_termios->c_cc[VQUIT] = 34;
		// new_termios->c_cc[VQUIT] = 25; // 25 = Ctrl-U ou Ctrl-X ^/
		new_termios->c_cc[VQUIT] = 3;
	}
	tcsetattr(0, TCSANOW, new_termios);
}

void ctrl_bs_unregister(void)
{
	if (old_termios)
	{
		printf("Unregister old termios\n");
		tcsetattr(0, TCSANOW, old_termios);
		free(new_termios);
		free(old_termios);
		old_termios = NULL;
	}
}
