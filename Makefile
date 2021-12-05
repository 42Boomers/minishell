CC					=	gcc
NAME				=	minishell
INCLUDES			=	includes/minishell.h
LIBS_PATH			=	libft/libft.a
LIBS_INCLUDES_DIR	=	-Iincludes -Ilibft -Ilibft/gnl -Ilibft/custom
LIBS_FLAG			=	-lreadline
OBJS_DIR			=	objs
SRCS_DIR			=	srcs
SRCS				=	$(shell find $(SRCS_DIR) -name "*.c")
OBJS				=	$(SRCS:$(SRCS_DIR)/%.c=$(OBJS_DIR)/%.o)
CFLAGS				=	-Wall -Wextra
#CFLAGS				=	-Wall -Wextra -Werror

all : $(NAME)

$(OBJS_DIR)/%.o:$(SRCS_DIR)/%.c $(INCLUDES)
	mkdir -p $(dir $@) && $(CC) -c $(LIBS_INCLUDES_DIR) $(LIBS_FLAG) $(CFLAGS) -o $@ $<

$(NAME) : $(OBJS)
	make -C libft full
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LIBS_PATH) $(LIBS_FLAG) 

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
