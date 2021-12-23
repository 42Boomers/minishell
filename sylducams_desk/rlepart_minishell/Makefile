NAME		=	minishell
PATH_SRC	=	srcs/
PATH_OBJ	=	objs/
SRC		=	ft_cd_pwd.c			\
			ft_display.c		\
			ft_edit_cmd.c		\
			ft_env.c			\
			ft_exec.c			\
			ft_export.c			\
			ft_signal.c			\
			ft_split_spaces.c	\
			ft_tools.c			\
			ft_unset.c			\
			ft_redir_lst.c		\
			ft_redirection.c	\
			ft_split_args.c		\
			ft_tools2.c			\
			ft_pipe.c			\
			ft_set_exit.c		\
			main.c
OBJ		=	$(addprefix $(PATH_OBJ), ${SRC:.c=.o})
HEADER		=	includes/minishell.h
RM		=	rm -rf
CC		=	clang
FLAGS		=	-g -Wall -Wextra -Werror
GNL			=	Get_Next_Line/Get_Next_Line.a
LIBFT		=	libft/libft.a

all:			$(NAME)

bonus:			all

$(PATH_OBJ)%.o:		$(PATH_SRC)%.c $(HEADER)
			@mkdir -p $(PATH_OBJ)
			$(CC) $(FLAGS) -c $< -o $@

GNL:
			@make -C Get_Next_Line/

Libft:
			@make bonus -C libft/

$(NAME):		GNL Libft $(OBJ) $(HEADER)
			@$(CC) $(FLAGS) $(OBJ) $(GNL) $(LIBFT) $(PRINTF) -o $(NAME)

clean:
			@make clean -C Get_Next_Line/
			@make clean -C libft/
			@$(RM) $(PATH_OBJ)

fclean:			clean
			@make fclean -C Get_Next_Line/
			@make fclean -C libft/
			@$(RM) $(NAME)

re:			fclean all

.PHONY: 		all clean fclean re bonus GNL Libft
