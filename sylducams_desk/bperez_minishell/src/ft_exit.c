/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: neben <neben@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 09:03:31 by ngeschwi          #+#    #+#             */
/*   Updated: 2021/11/29 13:24:48 by neben            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <limits.h>

static void	exit_else(t_shell *shell)
{
	write(1, "exit\n", 6);
	exit(shell->last_exit_status);
}

static int	ft_isspace(const int c)
{
	return ((c >= 9 && c <= 13) || c == ' ');
}

static unsigned long long	ft_atoull(char *str)
{
	unsigned long long	val;
	int					neg;

	val = 0;
	neg = 0;
	while (ft_isspace(*str))
		str++;
	if (*str == '-')
		neg = 1;
	if (neg || *str == '+')
		str++;
	while (ft_isdigit(*str))
		val = val * 10 + (*str++ - '0');
	if (neg)
		return (-val);
	return (val);
}

static int	check_number_range(char *str, unsigned long long num)
{
	unsigned long long	neg_num;
	unsigned long long	llong_max;

	if (str[0] == '-')
	{
		llong_max = LLONG_MAX;
		neg_num = ft_atoull(str + 1);
		if (neg_num > llong_max + 1)
			return (1);
	}
	else
	{
		if (num > LLONG_MAX)
			return (1);
	}
	return (0);
}

int	ft_exit(t_shell *shell)
{
	unsigned long long		nbr_exit;

	if (shell->command_list->argv[1]
		|| ft_strlen(shell->command_list->argv[1]) > 0)
	{
		nbr_exit = ft_atoull(shell->command_list->argv[1]);
		if ((nbr_exit == 0 && ft_strlen(shell->command_list->argv[1]) != 1)
			|| check_number_range(shell->command_list->argv[1], nbr_exit))
		{
			write(1, "exit\n", 6);
			printf("bash : exit: numeric argument required\n");
			exit(255);
		}
		else if (ft_tablen(shell->command_list->argv) > 2)
			printf("bash : exit: too many arguments\n");
		else
		{
			write(1, "exit\n", 6);
			exit(nbr_exit);
		}
	}
	else
		exit_else(shell);
	return (SUCCESS);
}
