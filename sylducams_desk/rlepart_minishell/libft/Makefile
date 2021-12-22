NAME		= libft
EXT			= .a
BSRCS		= ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c ft_lstlast_bonus.c ft_lstadd_back_bonus.c ft_lstdelone_bonus.c ft_lstclear_bonus.c ft_lstiter_bonus.c ft_lstmap_bonus.c
SRCS		= ft_atoi.c ft_bzero.c ft_calloc.c ft_free_tab.c ft_insert.c ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c ft_isspace.c ft_itoa.c ft_join_free.c ft_memccpy.c ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c ft_print_tab.c ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c ft_split.c ft_str_remove.c ft_stradd_back.c ft_strchr.c ft_strcmp.c ft_strdup.c ft_strjoin.c ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strmapi.c ft_strncmp.c ft_strnstr.c ft_strrchr.c ft_strstrdup.c ft_strtrim.c ft_substr.c ft_tolower.c ft_toupper.c ft_trim.c ft_xor.c
OBC			= $(SRCS:.c=.o)
BOBC		= $(BSRCS:.c=.o)
CC			= clang
CFLAGS		= -g -Wall -Wextra -Werror
RM			= rm -f
HEADER		= $(NAME).h

all:		$(NAME) $(HEADER)

$(NAME):	$(OBC) $(HEADER)
			@ar rc $(NAME)$(EXT) $(OBC)
			@ranlib $(NAME)$(EXT)

bonus:		$(OBC) $(BOBC) $(HEADER)
			@ar rc $(NAME)$(EXT) $(OBC) $(BOBC)
			@ranlib $(NAME)$(EXT)

$(OBC):		$(HEADER)

$(BOBC):	$(HEADER)

clean:
			@$(RM) $(OBC) $(BOBC)

fclean:		clean
			@$(RM) $(NAME)$(EXT)

re:			fclean all;

.PHONY: all clean fclean re
