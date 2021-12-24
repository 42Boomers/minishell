/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tglory <tglory@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 03:26:27 by tglory            #+#    #+#             */
/*   Updated: 2021/12/24 04:29:22 by tglory           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static struct termios *old_termios;
static struct termios *new_termios;


void ctrl_bs_register(void)
{
	// if (!new_termios)
	// {
	// 	old_termios = malloc(sizeof(*old_termios));
	// 	tcgetattr(0, old_termios);
	// 	new_termios = old_termios;
	// 	// new_termios->c_cc[VEOF] = 3;	 // ^C
	// 	// new_termios->c_cc[VINTR] = 4; // ^D
	// 	new_termios->c_cc[VSTOP] = 4;
	// }
	// tcsetattr(0, TCSANOW, new_termios);
}
/*
	char line[256];
	int len;
	do
	{
		len = read(0, line, 256);
		line[len] = '\0';
		if (len < 0)
			printf("(len: %i)", len);
		if (len == 0)
			printf("(VEOF)");
		if (len > 0)
		{
			if (line[len - 1] == 10)
				printf("(line:'%.*s')\n", len - 1, line);
			if (line[len - 1] != 10)
				printf("(partial line:'%s')", line);
		}
	} while (line[0] != 'q');
	*/
void ctrl_bs_unregister(void)
{
	// if (old_termios)
	// {
	// 	tcsetattr(0, TCSANOW, old_termios);
	// 	free(old_termios);
	// 	old_termios = NULL;
	// }
}
