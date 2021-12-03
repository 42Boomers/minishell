CC				=	gcc
NAME			=	minishell
LIBS_PATH		=	libft/libft.a
INCLUDES		=	$(wildcard includes)
INCLUDES_FOLDER	=	-Iincludes -Ilibft
SRCS			=	$(shell find srcs -name "*.c")
OBJS			=	$(SRCS:.c=.o)
CFLAGS			=	-Wall -Wextra
#CFLAGS			=	-Wall -Wextra -Werror

all : $(NAME)

%.o:%.c $(INCLUDES)
	$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES_FOLDER)

$(NAME) : $(OBJS)
	make -C libft all
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LIBS_PATH)

clean:
	make $@ -C libft
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re:
	make fclean
	make all

.PHONY: all clean fclean re