CC					=	gcc
NAME				=	minishell
INCLUDES			=	includes/minishell.h
LIBS_PATH			=	libft/libft.a
LIBS_INCLUDES_DIR	=	-Iincludes -Ilibft -Ilibft/gnl -Ilibft/custom
LIBS_FLAG			=	-lreadline -L ${HOMEBREW}/opt/readline/lib -I${HOMEBREW}/opt/readline/include
OBJS_DIR			=	objs
SRCS_DIR			=	srcs
SRCS				=	srcs/api/commands/commands_actions.c srcs/api/commands/commands_launch.c srcs/api/commands/commands_launch_utils.c \
						srcs/api/commands/commands_os.c srcs/api/commands/commands_register.c srcs/api/fork/ms_fork.c srcs/api/garbage/garbage.c \
						srcs/api/garbage/ms_malloc.c srcs/api/history/history_handler.c srcs/api/readline/ms_readline.c srcs/api/readline/ms_readline_utils.c \
						srcs/api/redirect/redirect.c srcs/api/utils/env_parse.c srcs/api/utils/env_parse2.c srcs/api/utils/env_parse3.c srcs/api/utils/env_parse_struct.c \
						srcs/api/utils/env_path.c srcs/api/utils/ft_join_chars.c srcs/api/utils/ft_print.c srcs/api/utils/ft_split_ultimate.c \
						srcs/api/utils/ft_str_build.c srcs/api/utils/ft_str_build2.c srcs/api/utils/utils_env.c srcs/api/utils/utils_env2.c \
						srcs/api/utils/utils_env3.c srcs/api/utils/utils_error.c srcs/api/utils/utils_file.c srcs/api/utils/utils_fork.c srcs/api/utils/utils_export.c \
						srcs/api/utils/utils_path.c srcs/api/utils/utils_redir.c srcs/api/utils/utils_redir2.c srcs/api/utils/utils_status.c \
						srcs/api/utils/utils_str.c srcs/api/utils/utils_var_parsing.c srcs/api/write/ms_write.c srcs/commands/cmd_export.c \
						srcs/commands/cmd_cd.c srcs/commands/cmd_echo.c srcs/commands/cmd_env.c srcs/commands/cmd_exit.c\
						srcs/commands/cmd_help.c srcs/commands/cmd_pwd.c srcs/commands/cmd_unset.c srcs/init/master_init.c srcs/api/utils/utils.c \
						srcs/main.c srcs/signals/handler_signal.c srcs/signals/handler_signal2.c srcs/test.c srcs/api/utils/ft_split_ultimate2.c \
						srcs/signals/handler_signal3.c srcs/api/utils/utils_2.c

OBJS				=	$(SRCS:$(SRCS_DIR)/%.c=$(OBJS_DIR)/%.o)
CFLAGS				=	-Wall -Wextra -Werror -g3

all : $(NAME)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c $(INCLUDES)
	mkdir -p $(dir $@) && $(CC) -c $(LIBS_INCLUDES_DIR) $(CFLAGS) -o $@ $< -I${HOMEBREW}/opt/readline/include

$(NAME) : $(OBJS)
	make -C libft full
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LIBS_PATH) $(LIBS_FLAG)

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
