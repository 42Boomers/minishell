CC		=	gcc
NAME	=	minishell
SRCS	=	$(wildcard srcs/*)
OBJS	=	$(SRCS:.c=.o)
CFLAGS	=	-Wall -Wextra #-Werror

all : $(NAME)

%.o:%.c $(INCLUDES)
	$(CC) $(CFLAGS) -c $< -o $@ -Iincludes

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