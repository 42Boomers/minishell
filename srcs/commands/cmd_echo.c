/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tglory <tglory@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 05:03:26 by tglory            #+#    #+#             */
/*   Updated: 2021/12/20 07:06:09 by tglory           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ms_env_parse_old(t_master *master, char *str)
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
		if (*str == '$' && !(*(str + 1)))
		{
			if (!build)
				return (ft_strdup("$"));
			else
				ft_str_add(build, ft_strdup("$"));
			break;
		}
		while (*str && *str != '$')
		{
			i++;
			str++;
		}
		if (i == 0 && !*str)
			return (ft_strdup(str));
		if (!build)
			build = ft_str_build_init();
		if (i != 0)
		{
			tmp = malloc(sizeof(char) * (i - k));
			if (!tmp)
				return (NULL); // cant malloc
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
			while (*str && (ft_isalnum(*str) || *str == '_'))
			{
				str++;
				i++;
			}
			tmp = malloc(sizeof(char) * (i - j));
			l = 0;
			while (i - 1 > j)
				tmp[l++] = str2[++j - (k + 1)];
			tmp[l] = 0;
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

int	n_check(char *first_arg)
{
	int	i;

	if (*first_arg == '-')
	{
		i = 0;
		while (first_arg[++i])
			if (first_arg[i] != 'n')
				return (FALSE);
		return (i > 1);
	}
	return (FALSE);
}

static t_bool	ms_echo_print_new(t_ms_input *input)
{
	int		arg_n;

	input->cmd->master->cmd_ret = 0;
	arg_n = 0;
	while (*input->args && n_check(*input->args))
	{
		arg_n = 1;
		input->args++;
	}
	while (*input->args)
	{
		ft_putstr(*input->args);
		if (*(input->args + 1))
			ft_putchar(' ');
		input->args++;
	}
	if (!arg_n)
		ft_putchar('\n');
	return (TRUE);
}

static char	*ms_echo_arg(t_ms_input *input, char *arg, int *arg_n, int i)
{
	if (!arg || !arg[0])
	{
		*arg_n = 0;
		return (NULL);
	}
	if (arg[0] == '-' && ft_strisfullof(arg + 1, 'n'))
	{
		*arg_n = 1;
		return (NULL);
	}
	return (ms_env_parse(input->cmd->master, arg));
}

static t_bool	ms_echo_print(t_ms_input *input)
{
	int			i;
	int			arg_n;
	char		*str;
	t_str_build	*build;

	i = -1;
	arg_n = 0;
	build = ft_str_build_init();
	if (!build)
		return (FALSE);
	build->separator = ft_strdup(" ");
	while (++i < input->args_size)
	{
		if (!input->args[i][0])
			continue ;
		if (input->args[i][0] == '-' && ft_strisfullof(input->args[i] + 1, 'n'))
		{
			arg_n = 1;
			continue ;
		}
		str = ms_env_parse(input->cmd->master, input->args[i]);
		if (!str)
			continue ;
		ft_str_add(build, str);
	}
	if (!arg_n)
		ft_str_add(build, ft_strdup("\n"));
	str = ft_str_build(build);
	printf(str);
	free(str);
	ft_str_destroy(build);
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
