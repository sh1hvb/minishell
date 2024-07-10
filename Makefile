
CFLAGS = -Wall -Wextra -Werror -fsanitize=address

NAME = minishell

NAME_LIBFT = libft/libft.a

LIBFT_PATH = libft/

SRC_MCHIHAB = main.c \
	execution/myenv.c execution/ft_export.c execution/utils_env.c \
	execution/builtins_checker.c execution/ft_pwd.c execution/ft_unset.c execution/ft_echo.c \
	execution/builtins_split.c execution/ft_cd.c execution/cmds/check_cmd.c execution/cmds/redirection.c execution/cmds/execute.c execution/ft_exit.c \
<<<<<<< HEAD
	execution/cmds/here_doc.c execution/cmds/heredoc_expand.c  #execution/cmds/create_pipes.c \
	execution/cmds/mult_cmds.c execution/cmds/run_cmd.c execution/cmds/single_cmd.c
=======
	execution/cmds/here_doc.c execution/cmds/heredoc_expand.c execution/cmds/single_cmd.c \
	execution/cmds/utils_exec.c
>>>>>>> main

SRC_SMARSI =  parsing/parsing.c parsing/quotes_remover.c parsing/signal.c parsing/helpers.c parsing/linked_list/pars_lst.c parsing/linked_list/heredoc_lst.c parsing/syntax/pipe_syntax.c parsing/syntax/syntax.c parsing/syntax/quotes_syntax.c parsing/syntax/files_syntax.c\
	helpers/errors.c\
	lexer/lexer.c lexer/lexer_helper.c lexer/lexer_split.c lexer/lexer_strchr.c lexer/lexer_functions.c \
	memory_handling/memory_handling.c memory_handling/memory_helpers.c \
	expand/expand.c libft_ftmalloc/free_libft.c libft_ftmalloc/ft_split.c ft_print.c


OBJ_MCHIHAB = $(SRC_MCHIHAB:.c=.o)

OBJ_SMARSI = $(SRC_SMARSI:.c=.o)

all : $(NAME)

$(NAME) : $(OBJ_SMARSI) $(OBJ_MCHIHAB)
	make -C $(LIBFT_PATH)
	cc $(CFLAGS) -lreadline  $(OBJ_SMARSI) $(OBJ_MCHIHAB) $(NAME_LIBFT) -o  $(NAME)

clean :
	make clean -C $(LIBFT_PATH)
	rm -f $(OBJ_SMARSI) $(OBJ_MCHIHAB)

re : fclean all

fclean : clean
	make fclean -C $(LIBFT_PATH)
	rm -f $(NAME)

.SECONDARY : $(OBJ_SMARSI) $(OBJ_MCHIHAB)

run : re clean
	./minishell