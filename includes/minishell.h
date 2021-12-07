/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tglory <tglory@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 02:20:26 by tglory            #+#    #+#             */
/*   Updated: 2021/12/07 02:14:02 by tglory           ###   ########lyon.fr   */
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
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>
# include <errno.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <dirent.h>

/*-----------------------------{ BOOLEAN }-----------------------------*/
typedef enum s_bool
{
	NONE = -1,
	FALSE = 0,
	TRUE = !FALSE
}	t_bool;

/*--------------------------{ MAIN STRUCT }--------------------------*/
typedef struct s_master
{
	char	**pwd;
	char	**old_pwd;
	int		last_status;
	// char	*home;
	// char	*user;
	// char	*shell;
	// char	*tmp;
	int		av;
	char	**ag;
	// char	**raw_envs;
	char	***envs;
	char	**paths;
	int		envs_size;
	char	*hist_file;
	t_list	*free_function;
	t_list	*cmds;
	t_bool	verbose;
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

/*----------------------------{ STR BUILD }----------------------------*/
typedef struct s_str_build
{
	t_list	*lst;
	int		char_size;
	int		lst_size;
	char	*separator;
}	t_str_build;

/*--------------------------{ COMMAND INPUT }--------------------------*/
typedef struct s_ms_input
{
	char					**args;
	int						args_size;
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
	char		*description;
	char		**default_args;
	int			default_args_size;
	t_bool		(*analyze)(t_ms_input *);
	t_bool		(*execute)(t_ms_input *);
	t_bool		(*print)(t_ms_input *);
	t_master	*master;
}	t_ms_command;

/*----------------------------{ MINISHELL }----------------------------*/

t_master		*ms_init_master(int av, char **ag, char **ev);
void			ms_free_master(t_master	*master);
t_bool			ms_test_cmd(t_master *master);
t_bool			ms_readline(t_master *master);
void			ms_register_signals(t_master *master);

/*-------------------------------{ API }-------------------------------*/

void			ft_println(char *str);
void			ft_println_orange(char *str);
void			ft_println_red(char *str);
t_bool			ms_str_equals(char *str1, char*str2);
t_bool			ms_str_equals_ignore(char *str1, char *str2);
t_bool			ms_env_init(t_master *master, char **envs);
char			*ms_env_get(t_master *master, char *key);
char			**ms_env_format(t_master *master);
char			*ms_pwd(t_master *master);
void			ms_write(char **array, int size);
void			ms_fork(t_master *master, void child(t_master *));
char			**ms_env_path_get(t_master *master);
char			**ms_env_path_refresh(t_master *master);
t_bool			ms_file_can_use(char *fname);
t_bool			ms_file_is_dir(char *dname);
void			mv_set_status(t_master *master, int status);
char			**ms_env_set(t_master *master, char *key, char *value);
void			ms_pwd_set(t_master *master, char *new_pwd);

/*----------------------------{ API CMDS }-----------------------------*/

t_ms_command	*ms_cmd_register(char *name, char *description,
					t_master *master, t_bool (*reg) (t_ms_command *));
void			ms_cmd_register_all(t_master *master);
t_ms_command	*ms_cmd_launch(t_master *master, char *command,
					char **args, int args_size);
t_bool			ms_cmd_os(t_master *master, char *command,
					char **args);
t_bool			ms_cmd_os_run(t_master *master, char *command,
					char **argv, char **env);
t_bool			ms_launch_at_start(t_master *master);
t_bool			mv_history_read(t_master *master);
t_bool			mv_history_write(t_master *master, char *command);

/*------------------------------{ CMDS }-------------------------------*/

t_bool			ms_cmd_env_register(t_ms_command *cmd);
t_bool			ms_cmd_pwd_register(t_ms_command *cmd);
t_bool			ms_cmd_help_register(t_ms_command *cmd);
t_bool			ms_cmd_echo_register(t_ms_command *cmd);
t_bool			ms_cmd_cd_register(t_ms_command *cmd);

/*-----------------------------{ GARBAGE }-----------------------------*/
void			*ms_malloc(t_list **garbage, size_t size);
void			*ms_malloc_custom(t_list **garbage, size_t size,
					void (*free_func) (void *));
void			*ms_malloc_master(t_master *master, size_t size);
void			ms_garbage_default_add(t_master *master, void *ptr,
					void (*free_func) (void *));
void			ms_garbage_add(t_list **garbage, void *ptr,
					void (*free_func) (void *));
void			ms_garbage_free(t_list **garbage);
void			ms_lstclear(void *arg);

#endif