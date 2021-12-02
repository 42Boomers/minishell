CC				=	gcc
NAME			=	minishell
INCLUDES		=	includes/minishell.h
INCLUDES_FOLDER	=	-Iincludes -Ilibft
SRCS			=	$(shell find . -name "*.c")
OBJS			=	$(SRCS:.c=.o)
CFLAGS			=	-Wall -Wextra
#CFLAGS			=	-Wall -Wextra -Werror

all : $(NAME)

%.o:%.c $(INCLUDES)
	$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES_FOLDER)

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re:
	make fclean
	make all

.PHONY: all clean fclean re