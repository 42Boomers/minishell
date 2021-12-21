CC					=	gcc
NAME				=	minishell
INCLUDES			=	includes/minishell.h
LIBS_PATH			=	libft/libft.a
LIBS_INCLUDES_DIR	=	-Iincludes -Ilibft -Ilibft/gnl -Ilibft/custom
LIBS_FLAG			=	-lreadline -L /Users/$(USER)/.brew/opt/readline/lib -I/Users/$(USER)/.brew/opt/readline/include
# LIBS_FLAG			=	-lreadline -L
# LIBS_FLAG			=	-lreadline -L /usr/local/Homebrew/opt/readline/lib -I/usr/local/Homebrew/opt/readline/include
OBJS_DIR			=	objs
SRCS_DIR			=	srcs
SRCS				=	$(shell find $(SRCS_DIR) -name "*.c") # TODO change to brut files names
OBJS				=	$(SRCS:$(SRCS_DIR)/%.c=$(OBJS_DIR)/%.o)
# OBJS				=	$(addprefix $(OBJS_DIR)/, $(notdir $(SRCS:$(SRCS_DIR)/%.c=%.o)))
CFLAGS				=	-Wall -Wextra -g
#CFLAGS				=	-Wall -Wextra -Werror

all : $(NAME)
	

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c $(INCLUDES)
# $(OBJS): $(SRCS) $(INCLUDES)
	mkdir -p $(dir $@) && $(CC) -c $(LIBS_INCLUDES_DIR) $(CFLAGS) -o $@ $< -I/Users/$(USER)/.brew/opt/readline/include

# $(NAME) : $(shell mkdir $(OBJS_DIR)) $(OBJS)
$(NAME) : $(OBJS)
	make -C libft full
<<<<<<< HEAD
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LIBS_PATH) $(LIBS_FLAG) -L /Users/$(USER)/.brew/opt/readline/lib
=======
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LIBS_PATH) $(LIBS_FLAG)
>>>>>>> 3ea9e75e5275026d1d452d54ffbe31d57a29f107

clean:
	rm -f $(OBJS)

fclean: clean
	make $@ -C libft
	rm -rf $(OBJS_DIR)
	rm -f $(LIBS_PATH) $(NAME)

re:
	make fclean
	make all

.PHONY: all clean fclean re
