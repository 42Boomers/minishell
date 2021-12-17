/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_tests.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sylducam <sylducam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 13:47:56 by sylducam          #+#    #+#             */
/*   Updated: 2021/12/17 14:02:18 by sylducam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdio.h>

void	handler(int sig)
{
	dprintf(1, "ctrl-c OK\n");
}

int	main(void)
{
	struct sigaction sa;
	sa.sa_handler = &handler;
	while (1)
		sigaction(SIGINT, &sa, NULL);
	return(0);
}