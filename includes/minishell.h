/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tglory <tglory@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 02:20:26 by tglory            #+#    #+#             */
/*   Updated: 2021/12/05 01:27:36 by tglory           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include "get_next_line.h"
# include "custom.h"
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>

/*--------------------------{ MAIN STRUCT }--------------------------*/
typedef struct s_master
{
	char	*pwd;
	char	*home;
	char	*user;
	char	*shell;
	char	*tmp;
	int		av;
	char	**ag;
	char	**envs;
	t_list	*free_function;
	t_list	*cmds;
}	t_master;

/*-----------------------------{ GARBAGE }-----------------------------*/
// typedef struct s_garbage
// {
// 	t_list	*lst;
// 	char	*(*get_key)(void *);
// 	void	(*free_func)(void *);
// }	t_garbage;

/*----------------------------{ AUTO FREE }----------------------------*/
typedef struct s_free_function
{
	void	*ptr;
	void	(*free_func)(void *);
}	t_free_function;

/*-----------------------------{ BOOLEAN }-----------------------------*/
typedef enum s_bool
{
	FALSE = 0,
	TRUE = !FALSE
}	t_bool;

/*--------------------------{ COMMAND INPUT }--------------------------*/
typedef struct s_ms_input
{
	char					**args;
	int						length;
	void					*data;
	struct s_ms_command		*cmd;
	t_list					*garbage;
}	t_ms_input;

typedef struct s_ms_cmd_env
{
	char					**raw_envs;
	char					***envs;
	int						envs_size;
	t_list					*free_function;
}	t_ms_cmd_env;

/*-----------------------------{ COMMAND }-----------------------------*/
typedef struct s_ms_command
{
	char		*name;
	t_bool		(*analyze)(t_ms_input *);
	t_bool		(*execute)(t_ms_input *);
	t_bool		(*print)(t_ms_input *);
	t_master	*master;
}	t_ms_command;

/*----------------------------{ MINISHELL }----------------------------*/

t_master		*ms_init_master(int av, char **ag, char **ev);
void			ms_free_master(t_master	*master);

/*-------------------------------{ API }-------------------------------*/

char			**ft_env_get(char *env);
void			ft_env_print_all(char **envs);
void			ft_println(char *str);
void			ft_println_orange(char *str);
void			ft_println_red(char *str);

/*----------------------------{ API CMDS }-----------------------------*/

t_ms_command	*ms_cmd_register(char *name, t_master *master,
					t_bool (*reg) (t_ms_command *));
void			ms_cmd_register_all(t_master *master);
t_ms_command	*ms_cmd_launch(t_master *master, char *command,
					char **args, int length);

/*------------------------------{ CMDS }-------------------------------*/

t_bool			ms_cmd_env_register(t_ms_command *cmd);

/*-----------------------------{ GARBAGE }-----------------------------*/
void			*ms_malloc(t_list **garbage, size_t size);
void			*ms_malloc_master(t_master *master, size_t size);
void			ms_garbage_default_add(t_master *master, void *ptr,
					void (*free_func) (void *));
void			ms_garbage_add(t_list **garbage, void *ptr,
					void (*free_func) (void *));
void			ms_garbage_free(t_list **garbage);
void			ms_lstclear(void *arg);

#endif