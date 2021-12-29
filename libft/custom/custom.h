/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   custom.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblache <jblache@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 22:07:01 by jblache           #+#    #+#             */
/*   Updated: 2021/12/29 18:34:47 by jblache          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUSTOM_H
# define CUSTOM_H

# include "libft.h"

/*-------------------------------{ BASICS }-------------------------------*/
int		ft_isequals_ignore(char *str1, char *str2);
int		ft_isequals(char *str1, char *str2);
int		ft_isblank(char *str);
void	*ft_realloc(void *ptr, size_t new_size, size_t old_size);

/*-------------------------------{ CUSTOM }-------------------------------*/
void	*ft_lstget(t_list *lst, char *key,
			char *(*get_key) (void *));
void	*ft_lstget_ignore(t_list *lst, char *key,
			char *(*get_key) (void *));
void	ft_lstremove(t_list **lst, char *key,
			char *(*get_key) (void *), void (*f) (void *));

/*--------------------------------{ PERSO }--------------------------------*/
char	**ft_strtrunc(char *str, char c);
char	*ft_strjoin_plus(char const *s1, char const *s2,
			char const *s3);

#endif
