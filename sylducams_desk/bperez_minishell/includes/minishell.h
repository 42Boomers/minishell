/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngeschwi <nathan.geschwind@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 16:07:27 by ngeschwi          #+#    #+#             */
/*   Updated: 2021/11/25 17:22:45 by ngeschwi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <signal.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <string.h>
# include <sys/errno.h>
# include <stdio.h>
# include <string.h>

typedef struct s_command
{
	int					argc;
	char				**argv;
	char				*program_path;
	int					redirection_in;
	int					redirection_out;
	int					fd_in;
	int					fd_out;
	char				**delimiters;
	struct s_shell		*shell;
	struct s_command	*prev;
	struct s_command	*next;
}	t_command;

typedef struct s_shell
{
	t_command	*command_list;
	char		**prompt_history;
	int			history_fd;
	char		**env;
	char		**all_path;
	int			index;
	int			pipe_fd[3][2];
	int			pipe_export[2];
	int			pipe_fd_redi_din[2];
	int			parsing_error;
	int			last_exit_status;
	int			last_errno;
}				t_shell;

# define SUCCESS 0
# define ERROR 1
# define EXIT_CMD 2
# define REDIRECTION_INPUT 1
# define REDIRECTION_OUTPUT 2
# define REDIRECTION_DINPUT 3
# define REDIRECTION_DOUTPUT 4
# define SPLIT_DELIMITER 1
# define ERRNO_DEFAULT_VALUE 256
# define FILE_NOT_FOUND 

// ***** Variable global *****

int	g_process_section;

// ***** Init data and signals *****
void		init_shell(t_shell *shell, char **env);
int			init_pipe(t_shell *shell);
void		exit_shell(void);

// ***** Parsing *****
int			parse_prompt(t_shell *shell, char *prompt);
int			split_command(char **command);
int			parse_argv(t_command *current_command, char **split_command);
int			parse_redirection(t_command *command, char **split_command);
t_command	*goto_first_command(t_command *current);
void		check_quotes(char c, int *quote, int *double_quote);
int			interpret_quotes(char **split_command, int *i, int *quote, int *dq);
int			expand_exit_status_variable(t_command *command,
				char **split_cmd, int i);
int			expand_env_variable(t_command *command,
				char **split_command, int i);
int			expand_tilde(t_command *command, char **split_cmd, int i);
void		replace_split_spaces(char *command);
int			parse_delimiter(t_command *command, char **split_command);
int			add_delimiter_to_list(t_command *command, char **split_command);
int			add_delimiters_to_redirection(char **command, int *i);
int			open_redirection_file(t_command *command, char *arg, int type);
char		*add_char(char *str, int index, char c);
int			check_commad_1(t_shell *shell);
int			check_commad_2(t_shell *shell);
void		rm_quotes_on_cmd(t_shell *shell);

// ***** Execution *****
void		execute_command(t_shell *shell);
void		do_after_cmd(t_shell *shell);
void		exec_cmd_for_rdi(t_shell *shell);
void		free_prompt(t_shell *shell, char *prompt);
void		close_pipe_rdi(t_shell *shell);
int			ft_pwd(t_shell *shell);
int			ft_echo(t_shell *shell);
int			ft_cd(t_shell *shell);
int			ft_env(t_shell *shell);
int			ft_export(t_shell *shell);
int			check_add(t_shell *shell, char **tab);
int			ft_unset(t_shell *shell);
int			ft_exit(t_shell *shell);
char		*ft_get_path(t_shell *shell);
char		**ft_get_arg(t_shell *shell);
char		*get_pwd(t_shell *shell);

// ***** Utils *****
void		*ft_tmp(void *a, void *b);
size_t		ft_strclen(const char *str, const char c);
void		ft_bzero(void *s, size_t n);
void		*ft_calloc(const size_t count, const size_t size);
void		*ft_memset(void *ptr, const unsigned int c, size_t len);
char		*ft_substr(const char *s, unsigned int start, size_t len);
char		**ft_split(char const *s, char c);
int			ft_strcmp(const char *s1, const char *s2);
char		*ft_strjoin(const char *s1, const char *s2);
int			ft_strlen(const char *str);
int			ft_tablen(char **tab);
char		*ft_strdup(char *src);
void		ft_error_fork(t_shell *shell, char *str);
void		free_tab(char **tab);
int			ft_error(char *str, int wich_one);
char		*ft_strtrim(const char *s1);
char		*ft_strndup(const char *s1, size_t len);
void		ft_free_2d(void **array, size_t size);
size_t		ft_strlen_2d(char **array);
int			ft_isalnum(const int c);
int			ft_isalpha(const int c);
int			ft_isdigit(const int c);
int			ft_strncmp(const char *s1, const char *s2, const size_t n);
int			get_current_env_int(t_shell *shell, char *str);
char		*get_current_env(t_shell *shell, char *str);
void		check_pwd(t_shell *shell);
int			change_env_cd(t_shell *shell);
void		send_env(t_shell *shell);
char		*ft_itoa(const int n);
int			ft_atoi(const char *str);
void		do_redirection_in(t_shell *shell);
void		do_redirection_out(t_shell *shell);
char		*ft_strchr(const char *s, const int c);
void		*ft_strccpy(char *dst, const char *src, const char c);

#endif
