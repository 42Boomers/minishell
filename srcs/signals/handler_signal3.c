/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_signal3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblache <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 17:07:05 by jblache           #+#    #+#             */
/*   Updated: 2021/12/29 17:07:07 by jblache          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_termios_echo(void)
{
	int				rc;
	struct termios	*saved;
	struct termios	attributes;

	saved = ms_mallocw(sizeof(*saved), "Cannot malloc termios");
	if (!saved)
		return ;
	rc = tcgetattr(STDIN_FILENO, saved);
	if (rc)
	{
		perror("tcgetattr");
		exit(1);
	}
	termios_restore(saved);
	tcgetattr(STDIN_FILENO, &attributes);
	attributes.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &attributes);
}
