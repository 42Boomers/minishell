/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_tests.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sylducam <sylducam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 13:47:56 by sylducam          #+#    #+#             */
/*   Updated: 2021/12/18 15:27:59 by sylducam         ###   ########.fr       */
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

// int		main(int n, char **arg, char **env)
// {
// 	t_content	content;

// 	if (n == 1)
// 	{
// 		ft_init(&content, env);
// 		ft_sigint(0, &content);
// 		ft_sigquit(0, &content);
// 		signal(SIGINT, ((void (*)(int))ft_sigint));
// 		signal(SIGQUIT, ((void (*)(int))ft_sigquit));
// 		ft_loop(&content);
// 	}
// 	else
// 		arg[0] = NULL;
// 	return (0);
// }

// SIGNAUX-----------------------------

// void	ft_sigquit(int signal, void *content)
// {
// 	static t_content	*save = NULL;

// 	signal = 0;
// 	if (!save)
// 		save = content;
// 	else if (save->pid > 0)
// 	{
// 		kill(save->pid, SIGQUIT);
// 		ft_putstr_fd("Quit : 3\n", 1);
// 	}
// }

// void	ft_sigint(int signal, void *content)
// {
// 	static t_content	*save = NULL;

// 	signal = 0;
// 	if (!save)
// 		save = content;
// 	else
// 	{
// 		write(1, "\n", 1);
// 		if (save->pid == -1)
// 		{
// 			ft_putstr_fd("pid = -1\n", 2);
// 			ft_putstr_fd("minishell -> ", 1);
// 		}
// 		else if (save->pid)
// 		{
// 			ft_putstr_fd("positive pid\n", 2);
// 			kill(save->pid, SIGINT);
// 		}
// 		else
// 			ft_putstr_fd("pid = 0\n", 2);
// 	}
// }