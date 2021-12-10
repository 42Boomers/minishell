/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tglory <tglory@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 05:03:26 by tglory            #+#    #+#             */
/*   Updated: 2021/12/10 06:49:06 by tglory           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ms_env_parse(t_master *master, char *str)
{
	char	*tmp;
	char	*str2;
	int		i;
	int		j;
	int		k;
	int		l;
	char	*env;
	t_str_build	*build;

	i = 0;
	k = -1;
	build = NULL;
	str2 = str;
	while (*str)
	{
		while (*str && *str != '$')
		{
			i++;
			str++;
		}
		if (!*str && !build)
			return (NULL);
		if (!build)
			build = ft_str_build_init();
		if (i != 0)
		{
			tmp = malloc(sizeof(char) * (i - k));
			if (!tmp)
				return (NULL); 	// cant malloc
			ft_strlcpy(tmp, str2, i - k);
			ft_str_add(build, tmp);
		}
		j = i++;
		str++;
		if (*str == '?')
		{
			str++;
			i++;
			ft_str_add(build, ft_itoa(master->last_status));
		}
		else
		{
			while (*str && (ft_isalnum(*str)))
			{
				str++;
				i++;
			}
			if (i == j)
			{
				ft_str_destroy(build);
				return (NULL); // arg is only $
			}
			tmp = malloc(sizeof(char) * (i - j));
			l = 0;
			while (i - 1 > j)
				tmp[l++] = str2[++j - (k + 1)];
			tmp[l] = 0;
			// env = getenv(tmp);
			env = ms_env_get(master, tmp);
			free(tmp);
			if (env)
				ft_str_add(build, ft_strdup(env));
		}
		str2 = str;
		k = i++;
	}
	tmp = ft_str_build(build);
	ft_str_destroy(build);
	return (tmp);
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
		if (str)
		{
			ft_putstr(str);
			free(str);
		}
		else
			ft_putstr(input->args[i]);
		if (i + 1 < input->args_size)
			ft_putchar(' ');
	}
	if (!arg_n)
		ft_putchar('\n');
	return (TRUE);
}

t_bool	ms_cmd_echo_register(t_ms_command *cmd)
{
	char	**args;
	int		i;
	
	// cmd->analyze = &ms_echo_analyze;
	// cmd->execute = &ms_echo_execute;
	cmd->print = &ms_echo_print;
	i = 0;
	args = malloc(sizeof(char *) * 6);
	args[i++] = "Hello";
	args[i++] = "World\n";
	args[i++] = "\"Ceci est un test\"\n";
	args[i++] = "$NAME\n";
	args[i++] = "$PATH";
	args[i++] = "\n$PWD_$NAME";
	ms_cmd_register_default_args(cmd, args, i);
	return (TRUE);
}

/*
static char	**ms_env_quote_simple(t_master *master, char **args)
{
	char	**out;
	char	*tmp;
	int		i;
	int		i1;
	int		i2;
	int		size;
	int		s1;
	int		s2;
	t_str_build	*build;

	i1 = 0;
	i2 = 0;
	i = 0;
	size = 0;
	while (args[i1][i2] && args[i1][i2] != '\'')
	{
		i2++;
		if (!args[i1][i2])
		{
			i1++;
			i2 = 0;
		}
	}
	if (!args[i1][i2])
		return (NULL);
	s1 = i1;
	s2 = i2 + 1;
	if (!args[i1][i2])
	{
		i1++;
		i2 = 0;
	}
	while (args[i1][i2] && args[i1][i2] != '\'')
	{
		size++;
		i2++;
		if (!args[i1][i2])
		{
			i1++;
			i2 = 0;
		}
	}
	if (!args[i1][i2])
		return (NULL);
	return (out);
}*/
/*
static char	*ms_env_quote_simple(t_master *master, char *str)
{
	char	*tmp;
	int		i;
	int		j;
	t_str_build	*build;

	i = 0;
	while (str[i] && str[i] != '\'')
		i++;
	if (!str[i])
		return (NULL);
	build = ft_str_build_init();
	if (i != 0)
	{
		ft_strlcpy(tmp, str, i);
		ft_str_add(build, tmp);
	}
	j = i;
	while (str[i] && str[i] != '\'')
		i++;
	if (!str[i])
		return (NULL);

	return (tmp);
}*/
