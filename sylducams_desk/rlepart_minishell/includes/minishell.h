/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-kada <mel-kada@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 18:32:01 by rlepart           #+#    #+#             */
/*   Updated: 2021/03/11 21:55:46 by mel-kada         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include "../Get_Next_Line/get_next_line.h"

# include <signal.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/wait.h>

typedef struct	s_content
{
	pid_t			pid;
	int				exit;
	int				quote;
	char			**envp;
	int				index_cmd;
	char			*buf;
}				t_content;

enum
{
	WRITE,
	TRUNCATE,
	INPUT
};

typedef struct	s_redir_lst
{
	char				*filename;
	int					type;
	struct s_redir_lst	*next;
}				t_redir_lst;

int	g_saved_fd[2];

void			ft_cd(t_content *content, char *tab, int pipe);
void			ft_echo(t_content *content, char **tab);
void			ft_edit_env(t_content *content, char *name, char *value);
void			ft_edit_underscore(t_content *content, char **tab, int pipe);
int				ft_exec(t_content *content, char **tab, int pipe);
void			ft_export(t_content *content, char **tab, int pipe);
int				ft_free_buf(t_content *content, int pipe);
void			ft_free_tab(void *str);
char			*ft_get_env(t_content *content, char *name);
char			*ft_get_var(t_content *content, char *str);
int				ft_no_bs(char *str, int i);
int				ft_no_d_quote(char *str, int i);
int				ft_no_s_quote(char *str, int i);
void			ft_pars(t_content *content, char **tab, int pipe);
void			ft_print_env(t_content *content, char **env);
void			ft_pwd(void);
char			*ft_remove_quotes(char *str);
char			**ft_remove_bs(char **str);
char			*ft_remove_bs_q(char *str);
char			*ft_replace_errno(char *str);
void			ft_set_exit(t_content *content, char **tab, int pipe);
char			*ft_skip_spaces(char *str);
void			ft_sigint(int signal, void *content);
void			ft_sigquit(int signal, void *content);
void			ft_split_cmd(t_content *content, char *buff);
char			**ft_split_spaces(char *str);
void			ft_unset(t_content *content, char **tab, int pipe);
char			*ft_trim_cmd(char *str, int *tab);
char			**ft_split_spaces2(char *str);
int				ft_get_nbr_index(char **str);
int				ft_is_ignored(char const *str, char c, int index);
char			**ft_split_args(char *s, char c);
void			ft_throw_error(char *msg);
void			ft_pipe_move(int *old_fd, char **str, int *fd, int index);
int				ft_check_redir(char *str, int i);
int				ft_check_pipe(char *str);
void			ft_process(t_content *content, char **list);
void			ft_restore_fd();
t_redir_lst		*ft_redir_lst_new(char *name, int type);
t_redir_lst		*ft_redir_lst_last(t_redir_lst *lst);
void			ft_redir_lst_add(t_redir_lst **lst, t_redir_lst *elem);
void			ft_redir_lst_clear(t_redir_lst *lst);
int				ft_redir_parse(t_content *content, char **str);
void			ft_memfree(char **str);
int				ft_check_quotes(char *str);

#endif
