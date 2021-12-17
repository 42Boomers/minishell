/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-kada <mel-kada@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 16:56:03 by rlepart           #+#    #+#             */
/*   Updated: 2021/03/11 21:59:37 by mel-kada         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_exit(t_content *content)
{
	ft_free_tab(content->envp);
	write(1, "exit\n", 5);
	exit(errno);
}

void	ft_pars(t_content *content, char **tab, int pipe)
{
	if (!ft_strcmp(*tab, "exit"))
		ft_set_exit(content, tab, pipe);
	else if (!ft_strcmp(*tab, "pwd"))
		ft_pwd();
	else if (!ft_strcmp(*tab, "cd"))
		ft_cd(content, tab[1], pipe);
	else if (!ft_strcmp(*tab, "env"))
		ft_print_env(content, content->envp);
	else if (!ft_strcmp(*tab, "echo"))
		ft_echo(content, &(tab[1]));
	else if (!ft_strcmp(*tab, "unset"))
		ft_unset(content, &(tab[1]), pipe);
	else if (!ft_strcmp(*tab, "export"))
		ft_export(content, &(tab[1]), pipe);
	else if (tab[0][0] && ft_exec(content, tab, pipe))
		;
	else if (tab[0][0])
	{
		printf("minishell: %s: command not found\n", tab[0]);
		errno = 127;
	}
	else
		write(1, "\n", 1);
	ft_edit_underscore(content, tab, pipe);
	ft_restore_fd();
}

void	ft_loop(t_content *content)
{
	char	*buff;
	int		ret;

	buff = NULL;
	while (content->exit != 1)
	{
		content->quote = 0;
		ft_putstr_fd("minishell -> ", 1);
		content->pid = -1;
		ret = get_next_line(0, &buff);
		if (ret < 0)
			exit(1);
		if (ret == 0)
			content->exit = 1;
		else if (*buff)
		{
			ft_split_cmd(content, buff);
			if (content->quote)
				ft_putstr_fd("Error, multiline quote\n", 1);
		}
		if (buff)
			free(buff);
	}
	ft_exit(content);
}

void	ft_init(t_content *content, char **env)
{
	char	pwd[10000];

	content->pid = -1;
	content->index_cmd = 0;
	content->exit = 0;
	content->buf = NULL;
	content->envp = ft_strstrdup(env);
	if (!ft_get_env(content, "SHLVL"))
		ft_edit_env(content, "SHLVL", ft_strdup("SHLVL=1"));
	else
		ft_edit_env(content, "SHLVL", ft_join_free("SHLVL=",
					ft_itoa(ft_atoi(ft_get_env(content, "SHLVL")) + 1), 1));
	if (!ft_get_env(content, "PWD"))
	{
		getcwd(pwd, 9999);
		pwd[9999] = '\0';
		ft_edit_env(content, "PWD", ft_strjoin("PWD=", pwd));
	}
}

int		main(int n, char **arg, char **env)
{
	t_content	content;

	if (n == 1)
	{
		ft_init(&content, env);
		ft_sigint(0, &content);
		ft_sigquit(0, &content);
		signal(SIGINT, ((void (*)(int))ft_sigint));
		signal(SIGQUIT, ((void (*)(int))ft_sigquit));
		ft_loop(&content);
	}
	else
		arg[0] = NULL;
	return (0);
}
