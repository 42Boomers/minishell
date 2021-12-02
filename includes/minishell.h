/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tglory <tglory@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 02:20:26 by tglory            #+#    #+#             */
/*   Updated: 2021/12/02 18:58:52 by tglory           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>

typedef struct s_master
{
	char	*pwd;
	char	*home;
	char	*user;
	char	*shell;
	char	*tmp;
	t_list	*free_function;
}	t_master;

typedef struct s_free_function
{
	void	*ptr;
	void 	(*free_func) (void *);
}	t_free_function;


char		**ft_env_get(char *env);
void		ft_env_print_all(char **envs);
t_master	*ms_init_master(int av, char **ag, char **ev);
void		ms_free_master(t_master	*master);

#endif