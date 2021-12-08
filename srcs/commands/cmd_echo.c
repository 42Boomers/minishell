/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tglory <tglory@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 05:03:26 by tglory            #+#    #+#             */
/*   Updated: 2021/12/08 18:47:17 by tglory           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static t_bool	ms_echo_analyze(t_ms_input *input)
// {
// 	(void)input;
// 	return (TRUE);
// }

// static t_bool	ms_echo_execute(t_ms_input *input)
// {
// 	(void)input;
// 	return (TRUE);
// }

static char	*ms_env_parse(t_master *master, char *str)
{
	char	*tmp;
	int		i;
	int		j;
	int		k;
	char	*env;
	char	*cat;
	t_str_build	*build;

	i = 0;
	while (str[i] && str[i] != '$')
		i++;
	if (!str[i])
		return (NULL);
	build = ft_str_build_init();
	if (i != 0)
	{
		cat = malloc(sizeof(char) * (i + 1));
		if (!cat)
			return (NULL);
		ft_strlcpy(cat, str, i + 1);
		// printf("DEBUG %d %s\n", i, cat);
		ft_str_add(build, cat);
	}
	j = i;
	while (str[i] && (str[i] != ' ' || str[i] != '/'))
		i++;
	if (i == j)
	{
		ft_str_destroy(build);
		// if (i > 0)
		// {
			
		// }
		return (NULL);
	}
	tmp = malloc(sizeof(char) * (i - j));
	k = 0;
	while (i - 1 > j)
		tmp[k++] = str[++j];
	tmp[k] = 0;
	// cat = malloc(sizeof(char) * );
	// ft_strlcat();
	// env = getenv(tmp);
	env = ms_env_get(master, tmp);
	if (env)
		ft_str_add(build, ft_strdup(env));
	cat = ft_str_build(build);
	ft_str_destroy(build);
	free(tmp);
	return (cat);
}

static t_bool	ms_echo_print(t_ms_input *input)
{
	int		i;
	int		arg_n;
	char	*str;

	i = -1;
	arg_n = 0;
	while (++i < input->args_size)
	{
		if (ft_isequals_ignore("-n", input->args[i]))
		{
			arg_n = 1;
			continue ;
		}
		// ft_putstr(input->args[i]);
		str = ms_env_parse(input->cmd->master, input->args[i]);
		if (!str)
			ft_putstr(input->args[i]);
		else
		{
			ft_putstr(str);
			free(str);
		}
		if (i + 1 < input->args_size)
			ft_putchar(' ');
	}
	if (!arg_n)
		ft_putchar('\n');
	return (TRUE);
}

t_bool	ms_cmd_echo_register(t_ms_command *cmd)
{
	// cmd->analyze = &ms_echo_analyze;
	// cmd->execute = &ms_echo_execute;
	cmd->print = &ms_echo_print;
	return (TRUE);
}
