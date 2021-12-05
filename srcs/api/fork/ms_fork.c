/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_fork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tglory <tglory@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 10:07:29 by tglory            #+#    #+#             */
/*   Updated: 2021/12/05 10:14:23 by tglory           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_fork(t_master *master, void child(t_master *))
{
    pid_t cpid;
    pid_t wpid;
    int status;

    cpid = fork();
    if (cpid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    if (cpid == 0) {
		child(master);
    } else {
		status = -1;
        while (status == -1 || (!WIFEXITED(status) && !WIFSIGNALED(status)))
		{
            wpid = waitpid(cpid, &status, WUNTRACED | WCONTINUED);
            if (wpid == -1) {
                perror("waitpid");
                exit(EXIT_FAILURE);
            }
			if (WIFEXITED(status))
				printf("DEBUG terminé, code=%d\n", WEXITSTATUS(status));
			else if (WIFSIGNALED(status))
				printf("DEBUG tué par le signal %d\n", WTERMSIG(status));
			else if (WIFSTOPPED(status))
				printf("DEBUG arrêté par le signal %d\n", WSTOPSIG(status));
			else if (WIFCONTINUED(status))
				printf("DEBUG relancé\n");
        }
    }
}
