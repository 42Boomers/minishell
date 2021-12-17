NAME		=	Get_Next_Line
EXT			=	.a
SRCS		=	get_next_line.c \
				get_next_line_utils.c
OBC			=	$(SRCS:.c=.o)
CC			=	clang
CFLAGS		=	-g -Wall -Wextra -Werror
RM			=	rm -f
HEADER		=	get_next_line.h

all:		$(NAME)

$(NAME):	$(OBC) $(HEADER)
			@ar rc $(NAME)$(EXT) $(OBC)
			@ranlib $(NAME)$(EXT)

bonus:		all

$(OBC):		$(HEADER)

clean:
			@$(RM) $(OBC) $(BOBC)

fclean:		clean
			@$(RM) $(NAME)$(EXT)

re:			fclean all;

.PHONY: all clean fclean re bonus
