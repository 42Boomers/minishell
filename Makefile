CC				=	gcc
NAME			=	minishell
LIBS_PATH		=	libft/libft.a
INCLUDES		=	$(wildcard includes)
INCLUDES_FOLDER	=	-Iincludes -Ilibft
OBJ_DIR			=	objs
SRCS_DIR		=	srcs
SRCS			=	$(shell find srcs -name "*.c")
OBJS			=	$(SRCS:$(SRCS_DIR)/%.c=$(OBJ_DIR)/%.o)
CFLAGS			=	-Wall -Wextra
#CFLAGS			=	-Wall -Wextra -Werror

all : $(NAME)

$(OBJ_DIR)/%.o:$(SRCS_DIR)/%.c $(INCLUDES)
	mkdir -p $(dir $@)
	$(CC) -c $(INCLUDES_FOLDER) -o $@ $< $(CFLAGS)

$(NAME) : $(OBJS)
	make -C libft full
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LIBS_PATH)

clean:
	rm -f $(OBJS)
	rm -rf $(OBJ_DIR)

fclean: clean
	make $@ -C libft
	rm -f $(LIBS_PATH)
	rm -f $(NAME)

re:
	make fclean
	make all

.PHONY: all clean fclean re
