CC				=	gcc
NAME			=	minishell
LIBS_PATH		=	libft/libft.a
INCLUDES		=	$(wildcard includes)
INCLUDES_FOLDER	=	-Iincludes -Ilibft -Ilibft/gnl -Ilibft/custom
OBJS_DIR		=	objs
SRCS_DIR		=	srcs
SRCS			=	$(shell find $(SRCS_DIR) -name "*.c")
OBJS			=	$(SRCS:$(SRCS_DIR)/%.c=$(OBJS_DIR)/%.o)
CFLAGS			=	-Wall -Wextra
#CFLAGS			=	-Wall -Wextra -Werror

all : $(NAME)

$(OBJS_DIR)/%.o:$(SRCS_DIR)/%.c $(INCLUDES)
	mkdir -p $(dir $@) && $(CC) -c $(INCLUDES_FOLDER) $(CFLAGS) -o $@ $<

$(NAME) : $(OBJS)
	make -C libft full
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LIBS_PATH)

clean:
	rm -f $(OBJS)
	rm -rf $(OBJS_DIR)

fclean: clean
	make $@ -C libft
	rm -f $(LIBS_PATH) $(NAME)

re:
	make fclean
	make all

.PHONY: all clean fclean re
