/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tglory <tglory@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 21:27:14 by tglory            #+#    #+#             */
/*   Updated: 2021/12/21 21:33:10 by tglory           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_print_error(char *prog_name, char *cmd_name)
{
	char	*error;

	error = ft_strjoin_plus(prog_name, ": ", cmd_name);
	perror(error);
	free(error);
}

void	ms_print_error_cmd(t_ms_input *input)
{
	ms_print_error(input->cmd->master->name, input->cmd->name);
}
