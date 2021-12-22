/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-kada <mel-kada@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 15:30:46 by rlepart           #+#    #+#             */
/*   Updated: 2021/03/11 20:47:05 by mel-kada         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		ft_execve(char *cmd, char **tab, t_content *content)
{
	int		status;
	char	*str_error;

	content->pid = fork();
	if (content->pid == -1)
	{
		str_error = strerror(errno);
		ft_putstr_fd(str_error, 1);
		write(1, "\n", 1);
		return (-1);
	}
	else if (content->pid > 0)
	{
		waitpid(content->pid, &status, 0);
		kill(content->pid, SIGTERM);
		return (0);
	}
	else
		exit(execve(cmd, tab, content->envp));
}

char	*ft_get_exec(t_content *content, char *tab)
{
	char		**str;
	struct stat	stt;
	int			n[2];
	char		*line[2];

	if (((n[0] = 0) == 0) && stat(tab, &stt) == 0)
		return (ft_strdup(tab));
	if (!ft_get_env(content, "PATH"))
		printf("minishell: %s: No such file or directory\n", tab);
	if (!ft_get_env(content, "PATH"))
		return (NULL);
	if (!(str = ft_split(ft_get_env(content, "PATH"), ':')))
		exit(1);
	line[0] = ft_strjoin("/", tab);
	while (line[0] && str[n[0]] && (line[1] = ft_strjoin(str[n[0]], line[0])))
	{
		if (++(n[0]) && stat(line[1], &stt) == 0)
			break ;
		free(line[1]);
		line[1] = NULL;
	}
	ft_free_tab(str);
	if (line[0])
		free(line[0]);
	return (line[1]);
}

int		ft_exec(t_content *content, char **tab, int pipe)
{
	int		ret;
	char	*cmd;

	ret = 0;
	if (!(cmd = ft_get_exec(content, *tab)))
	{
		if (pipe)
			exit(0);
		else
			return (0);
	}
	free(*tab);
	*tab = cmd;
	if (!pipe && !content->buf)
		ret = (ft_execve(cmd, tab, content) != -1);
	else
	{
		execve(cmd, tab, content->envp);
	}
	return (ret);
}
