#MAKEFLAGS += --silent

NAME = minishell
CC = gcc
CFLAGS = -g3 -fsanitize=address -include stdio.h -I${includedir} -Wextra -Wall -Werror
INC_DIR = includes/
INC =	minishell.h

ifeq (, $(shell brew list readline))
 BREW := $(shell brew install readline)
endif

prefix=$(shell brew --prefix readline)
exec_prefix=${prefix}
libdir=${exec_prefix}/lib
includedir=${prefix}/include

SRC_DIR = src/
SRC =	main.c \
		init_data.c \
		parse_prompt.c \
		parse_argv.c \
		parse_redirection.c \
		parse_redirection2.c \
		expand_variables.c \
		utils.c \
		execute_command.c \
		execute_command_2.c \
		exec_cmd_for_rdi.c \
		ft_parse.c \
		ft_echo.c \
		ft_cd.c \
		ft_export.c \
		ft_export_2.c \
		ft_unset.c \
		ft_pwd.c \
		ft_env.c \
		ft_exit.c \
		utils/ft_split.c \
		utils/ft_strccpy.c \
		utils/ft_strcmp.c \
		utils/ft_strjoin.c \
		utils/ft_strlen.c \
		utils/ft_strdup.c \
		utils/ft_free.c \
		utils/ft_substr.c \
		utils/ft_bzero.c \
		utils/ft_calloc.c \
		utils/ft_memset.c \
		utils/ft_strclen.c \
		utils/ft_tmp.c \
		utils/ft_strtrim.c \
		utils/ft_strndup.c \
		utils/ft_free_2d.c \
		utils/ft_strlen_2d.c \
		utils/ft_isalnum.c \
		utils/ft_isalpha.c \
		utils/ft_isdigit.c \
		utils/ft_strncmp.c \
		utils/get_current_env.c \
		utils/check_pwd.c \
		utils/change_env_cd.c \
		utils/send_env_export.c \
		utils/ft_itoa.c \
		utils/ft_atoi.c \
		utils/do_redirection_in.c \
		utils/do_redirection_out.c \
		utils/ft_strchr.c

OBJ_DIR = .obj/
OBJ = $(SRC:%.c=$(OBJ_DIR)%.o)

.PHONY : all clean fclean re exec

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) -L${libdir} -lreadline $(CFLAGS) $(OBJ) -o $(NAME) -I $(INC_DIR) -lm

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(addprefix $(INC_DIR),$(INC))
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -I $(INC_DIR) -c $< -o $@

exec:
	./$(NAME)

norm:
	norminette

clean:
	/bin/rm -rf $(OBJ_DIR)

fclean: clean
	/bin/rm -f $(NAME)

re: 
	$(MAKE) fclean
	$(MAKE) all
