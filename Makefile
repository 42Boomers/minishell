CC					=	gcc
NAME				=	minishell
INCLUDES			=	includes/minishell.h
LIBS_PATH			=	libft/libft.a
LIBS_INCLUDES_DIR	=	-Iincludes -Ilibft -Ilibft/gnl -Ilibft/custom
LIBS_FLAG			=	-lreadline
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
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LIBS_PATH) $(LIBS_FLAG) -L /Users/$(USER)/.brew/opt/readline/lib

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
