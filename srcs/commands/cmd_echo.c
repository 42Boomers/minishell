/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tglory <tglory@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 05:03:26 by tglory            #+#    #+#             */
/*   Updated: 2021/12/21 02:21:16 by tglory           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
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
*/
static char	*ms_echo_arg(t_ms_input *input, char *arg, int *arg_n, int i)
{
	if (!input->args[i][0])
		return (NULL);
	if (input->args[i][0] == '-' && ft_strisfullof(input->args[i] + 1, 'n'))
	{
		*arg_n = 1;
		return (NULL);
	}
	return (arg);
}

static t_bool	ms_echo_print(t_ms_input *input)
{
	int			i;
	int			arg_n;
	char		*str;
	char		*tmp;
	t_str_build	*build;

	i = -1;
	arg_n = 0;
	build = ft_str_build_init();
	if (!build)
		return (FALSE);
	build->separator = ft_strdup(" ");
	while (++i < input->args_size)
	{
		str = ms_echo_arg(input, input->args[i], &arg_n, i);
		if (!str)
			continue ;
		ft_str_add(build, ft_strdup(str));
	}
	str = ft_str_build(build);
	if (!arg_n)
	{
		tmp = ft_strjoin(str, "\n");
		free(str);
		str = tmp;
	}
	printf(str);
	free(str);
	ft_str_destroy(build);
	return (TRUE);
}

t_bool	ms_cmd_echo_register(t_ms_command *cmd)
{
	char	**args;
	int		i;

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
