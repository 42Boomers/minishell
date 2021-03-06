/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tglory <tglory@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 02:20:26 by tglory            #+#    #+#             */
/*   Updated: 2021/12/28 17:14:32 by tglory           ###   ########lyon.fr   */
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
# include <string.h>
# include <termios.h> 

/*-----------------------------{ BOOLEAN }-----------------------------*/
typedef enum s_bool
{
	FALSE = 0,
	TRUE = !FALSE
}	t_bool;

/*--------------------------{ MAIN STRUCT }--------------------------*/
typedef struct s_master
{
	t_list	*garbage;
	t_list	*cmds;
	t_list	*envs;
	char	**pwd;
	char	**old_pwd;
	char	**av;
	char	**paths;
	char	*hist_file;
	char	*name;
	int		cmd_ret;
	int		last_status;
	int		ac;
	t_bool	verbose;
	pid_t	pid;
}	t_master;

/*------------------------------{ ENVS }------------------------------*/
typedef struct s_env
{
	char	*key;
	char	*value;
}	t_env;
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

/*--------------------------{ ENV PARSE }--------------------------*/
typedef struct s_env_parse
{
	t_master	*master;
	t_str_build	*build;
	char		*tmp;
	char		*str;
	char		*str2;
	char		*env;
	char		*out;
	int			i;
	int			j;
	int			k;
	int			l;
	t_bool		double_quote;
}	t_env_parse;

/*--------------------------{ COMMAND INPUT }--------------------------*/
typedef struct s_ms_input
{
	char					**args;
	int						args_size;
	void					*data;
	struct s_ms_command		*cmd;
	t_list					*garbage;
}	t_ms_input;

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
t_master		*ms_init_master(int ac, char **av, char **evs);
void			ms_free_master(t_master	*master);
t_bool			ms_test_cmd(t_master *master);
t_bool			ms_readline(t_master *master);
void			ft_sigint(void *master);
void			ft_sigquit(void *master);
int				ft_pipe_check(char **args);
void			ms_fork(t_master *master, char *command, \
				char **args, int args_size);
int				ms_red_in_out(char **args, int *redir);
int				ft_check_bad(int pos, char **args);
void			ms_check_redir(char **command, char **args);
int				ft_redir_error(int ret, char **args);
int				ms_redir_open(int *fd, char **args, int pos, int option);
int				ms_bad_redir_error(char **args, int pos);
int				ft_pres_red(char **args);
int				ft_red_pip_cmd(char **command, char **args, t_master *master);
void			ms_del_red(char **args, int pos);
void			ms_fork_init2(char **args, int *redir, int pip_end[2],
					int *fd_in);
int				ms_error_pipe(int pip_end[2]);
int 			ms_heredoc(int fd, char *s_eof);
void			register_signal_main(void);
void			register_signal_fork(void);
void			ctrl_c_fork(int signum, siginfo_t *sig_info, void *ucontext_t);
void			ctrl_c_normal(int signum, siginfo_t *sig_info,
					void *ucontext_t);
void			ctrl_bs_normal(int signum, siginfo_t *sig_info,	
					void *ucontext_t);
void			ctrl_bs_fork(int signum, siginfo_t *sig_info, void *ucontext_t);
void			ms_print_cmd_not_found(char *name, char *cmd);
t_list			*ms_env_lst_cpy(t_list *lst);
void			map_swap(t_env *arg1, t_env *arg2);
void			ms_fork_free(int fd_in, int pip_end0, int pip_end1);
char			*ms_pwd_buff(char *prog_name, char *command_name,
					int buff_size);
void			remove_termios_echo(void);
void			termios_restore(struct termios *term);

/*-------------------------------{ API }-------------------------------*/
void			ft_println(char *str);
void			ft_println_orange(char *str);
void			ft_println_red(char *str);
t_bool			ms_str_equals(char *str1, char*str2);
t_bool			ms_str_equals_ignore(char *str1, char *str2);
t_bool			ms_env_init(t_master *master, char **envs);
char			*ms_env_get(t_master *master, char *key);
void			ms_env_remove(t_master *master, char *key);
char			**ms_env_format(t_master *master);
char			**ms_env_replace(t_master *master, char *key, char *value);
void			ms_env_destroy(t_master *master);
char			**ms_env_path_get(t_master *master);
char			**ms_env_path_refresh(t_master *master);
char			*ms_env_parse(t_master *master, char *str, int quote);
t_env_parse		*ms_env_parse_create(t_master *master, char *str);
t_bool			ms_env_parse_str(t_env_parse *ep);
t_bool			ms_env_parse_search(t_env_parse *ep);
t_bool			ms_env_parse_var(t_env_parse *ep);
void			ms_env_path_free(t_master *master);
t_bool			ms_env_add_raw(t_master *master, char *env);
t_env			*ms_env_get_struct(t_master *master, char *key);
void			ms_env_free(void *arg);
char			*ms_env_key_get(void *arg);
t_env			*ms_env_create(char *raw_envs);
t_env			*ms_env_create_basic(char *key, char *value);
t_bool			ms_env_add(t_master *master, char *key, char *value);
t_bool			ms_env_parse_tilde(t_env_parse *ep);
char			*ms_pwd(t_master *master);
void			ms_write(char **array, int size);
t_bool			ms_file_can_use(char *fname);
t_bool			ms_file_is_dir(char *dname);
void			ms_set_status(t_master *master, int status);
void			ms_pwd_set(t_master *master, char *new_pwd);
char			**ft_split_ultimate(t_master *master, char const *s, char c);
char			*ft_fillstr2(t_master *master, const char *s, char *strs, \
				int m[4]);
char			*ft_fillstr3(const char *s, char *strs, int *n, int m[3]);
char			*ft_init_fillstr(int m[4], int n);
int				ft_ttabcrea2(const char *s, int n, char c, int *line);
int				ft_skip(const char *s, int n);
int				ft_skip2(const char *s, int n);
char			*ms_prefix_get(t_master *master);
char			**ft_join_chars(char **array1, char **array2);
void			ms_print_error(char *prog_name, char *cmd_name);
void			ms_print_error_cmd(t_ms_input *input);
t_bool			check_var_arg(char *arg);

/*----------------------------{ API CMDS }-----------------------------*/
t_ms_command	*ms_cmd_register(char *name, char *description,
					t_master *master, t_bool (*reg) (t_ms_command *));
void			ms_cmd_register_all(t_master *master);
t_ms_command	*ms_cmd_launch(t_master *master, char *command,
					char **args, int args_size);
t_bool			ms_cmd_os(t_master *master, char *command,
					char **args);
void			ms_cmd_os_run(t_master *master, char *command, char **argv,
					char **env);
t_bool			ms_launch_at_start(t_master *master);
t_bool			ms_history_read(t_master *master);
t_bool			ms_history_write(t_master *master, char *command);
void			ms_cmd_register_default_args(t_ms_command *cmd,
					char **default_args, int default_args_size);
char			*ms_cmd_get_key(void *arg);
t_ms_input		*ms_cmd_input(t_ms_command *cmd, char **args, int args_size);
t_bool			ms_cmd_execute(t_ms_input *input);

/*----------------------------{ API STR }-----------------------------*/
t_str_build		*ft_str_build_init(void);
void			ft_str_destroy(t_str_build *builder);
char			*ft_str_build(t_str_build *builder);
void			ft_str_add(t_str_build *builder, char *str);
char			**ft_str_array_build(t_str_build *builder);
t_bool			ft_strisfullof(char *str, char c);

/*------------------------------{ CMDS }-------------------------------*/
t_bool			ms_cmd_env_register(t_ms_command *cmd);
t_bool			ms_cmd_pwd_register(t_ms_command *cmd);
t_bool			ms_cmd_help_register(t_ms_command *cmd);
t_bool			ms_cmd_echo_register(t_ms_command *cmd);
t_bool			ms_cmd_cd_register(t_ms_command *cmd);
t_bool			ms_cmd_unset_register(t_ms_command *cmd);
t_bool			ms_cmd_export_register(t_ms_command *cmd);
t_bool			ms_cmd_exit_register(t_ms_command *cmd);

/*-----------------------------{ GARBAGE }-----------------------------*/
void			*ms_mallocw(size_t size, char *warning_message);
void			*ms_malloc(t_list **garbage, size_t size);
void			*ms_malloc_custom(t_list **garbage, size_t size,
					void (*free_func) (void *));
void			*ms_malloc_master(t_master *master, size_t size);
void			ms_garbage_master_add(t_master *master, void *ptr,
					void (*free_func) (void *));
void			ms_garbage_add(t_list **garbage, void *ptr,
					void (*free_func) (void *));
void			ms_garbage_free(t_list **garbage);
void			ms_lstclear(void *arg);

#endif