/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-kada <mel-kada@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/26 17:30:23 by mel-kada          #+#    #+#             */
/*   Updated: 2021/03/11 20:47:58 by mel-kada         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_redir_move_fd(t_redir_lst *lst, int fd)
{
	if (lst->type == INPUT)
	{
		g_saved_fd[0] = STDIN_FILENO;
		g_saved_fd[1] = dup(STDIN_FILENO);
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	else
	{
		g_saved_fd[0] = STDOUT_FILENO;
		g_saved_fd[1] = dup(STDOUT_FILENO);
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
}

int		ft_redir_perform(t_redir_lst *lst)
{
	int			fd;
	t_redir_lst	*last;

	last = NULL;
	while (lst)
	{
		if (lst->type == WRITE)
			fd = open(lst->filename, O_WRONLY | O_TRUNC | O_CREAT, 0666);
		if (lst->type == TRUNCATE)
			fd = open(lst->filename, O_APPEND | O_WRONLY | O_CREAT, 0666);
		if (lst->type == INPUT)
			fd = open(lst->filename, O_RDONLY);
		if (fd < 0)
		{
			ft_throw_error(strerror(errno));
			return (-1);
		}
		last = lst;
		lst = lst->next;
	}
	ft_redir_move_fd(last, fd);
	return (1);
}

void	ft_get_type(int *type, char *str, int *index)
{
	*type = str[*index] == '>' ? WRITE : INPUT;
	if (str[*index + 1] == '>')
	{
		*type = TRUNCATE;
		(*index)++;
	}
}

char	*ft_redir_algo(t_content *content, t_redir_lst **lst, char *str)
{
	int		i[3];
	char	**k;
	char	*save;

	i[0] = -1;
	while (str[++i[0]])
	{
		if ((str[i[0]] == '>' || str[i[0]] == '<') &&
			!ft_is_ignored(str, str[i[0]], i[0]))
		{
			i[1] = i[0];
			ft_get_type(&i[2], str, i);
			if (str[i[0] + 1] == 0)
				return (0);
			k = ft_split_spaces2(&(str[++i[0]]));
			ft_redir_lst_add(lst,
					ft_redir_lst_new(ft_remove_bs_q(ft_strdup(k[0])), i[2]));
			save = ft_redir_algo(content, lst, ft_trim(str, i[1],
				i[1] + (ft_strnstr(&(str[i[1]]), k[0], ft_strlen(&(str[i[1]])))
					- &(str[i[1]]) + ft_strlen(k[0]))));
			ft_free_tab(k);
			return (save);
		}
	}
	return (str);
}

int		ft_redir_parse(t_content *content, char **str)
{
	t_redir_lst	*lst;
	int			ret;

	lst = NULL;
	ret = 0;
	*str = ft_redir_algo(content, &lst, *str);
	if (lst != NULL)
	{
		ret = ft_redir_perform(lst);
		ft_redir_lst_clear(lst);
		if (!ret)
			ft_restore_fd();
		return (ret);
	}
	return (0);
}
