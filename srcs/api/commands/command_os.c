/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_os.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tglory <tglory@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 09:35:36 by tglory            #+#    #+#             */
/*   Updated: 2021/12/05 10:21:47 by tglory           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_bool ms_cmd_os_start(t_master *master, char *command,
				char **argv, char **env)
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
		execve(command, argv, env);
    } else {
		status = -1;
        while (status == -1 || (!WIFEXITED(status) && !WIFSIGNALED(status)))
		{
            wpid = waitpid(cpid, &status, WUNTRACED | WCONTINUED);
            if (wpid == -1) {
                perror("waitpid");
                exit(EXIT_FAILURE);
            }
			if (master->verbose)
			{
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
	return (TRUE);
}

static t_bool	ms_cmd_os_search(t_master *master,
				char *command, char **paths)
{
	char	*name;
	char	**argv;

	while (*paths)
	{
		name = ft_strjoin_plus(*paths++, "/", command);
		ms_garbage_default_add(master, name, free);
		if (!access(name, F_OK))
		{
			argv = ms_malloc_master(master, sizeof(char *) * 2);
			argv[0] = command;
			argv[1] = NULL;
			printf("DEBUG Prog found : '%s'\n", name);
			return (ms_cmd_os_start(master, name, argv, ms_env_format(master)));
		}
	}
	return (FALSE);
}

t_bool	ms_cmd_os(t_master *master, char *command,
		char **args)
{
	char	**paths;
	char	*path;
	int		i;
	
	path = ms_env_get(master, "PATH");
	if (!path)
		return (FALSE);
	paths = ft_split(path, ':');
	if (!paths)
		return (FALSE);
	i = 0;
	while (paths[i])
		ms_garbage_default_add(master, paths[i++], free);
	ms_garbage_default_add(master, paths, free);
	if (!paths[0])
	{
		free(paths);
		return (FALSE); 
	}
	return (ms_cmd_os_search(master, command, paths));
}

/*
void	ms_path_resolve(t_master *master)
{
	// char **paths;
	// char *path;
	// char *name;
	
	// path = ms_env_get(master, "PATH");
	// if (!path)
	// 	return ;
	// paths = ft_split(path, ":");
	// if (!paths)
	// 	return ;
	// ms_garbage_default_add(master, paths, free);
	// if (!paths[0])
	// 	return ;

	// while (*paths)
	// {
	// 	name = ft_strjoin(*path++, "/", command);
	// 	if (!access(name, F_OK))
	// 	{
	// 		execve("/bin/date", null, ms_env_format(master));
	// 	}
	// }
}*/
