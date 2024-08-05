
CFLAGS = -Wall -Wextra -Werror #-g3 #-fsanitize=address

NAME = minishell

NAME_LIBFT = libft/libft.a

LIBFT_PATH = libft/
SRC_CMDS = execution/cmds/check_cmd.c execution/cmds/execute.c execution/cmds/single_cmd.c \
	execution/cmds/utils_exec.c execution/cmds/errors_cmd.c execution/cmds/piping.c \
	execution/cmds/utils_single.c

SRC_RED = execution/redirections/redirection.c execution/redirections/here_doc.c \
		execution/redirections/heredoc_expand.c execution/redirections/linked_list_file.c \
		execution/redirections/utils_redirection.c execution/redirections/utils_heredoc.c

SRC_UTILS_BUILTS = execution/utils_builts/mini_utils_export.c  execution/utils_builts/utils_export.c 


SRC_BUILTS = execution/myenv.c execution/ft_export.c execution/utils_env.c  execution/init_env.c \
 			execution/ft_exit.c execution/builtins_checker.c execution/ft_pwd.c execution/ft_unset.c execution/ft_echo.c \
			execution/builtins_split.c execution/builtins_split_helper.c execution/ft_cd_helper.c \
			execution/ft_cd.c execution/linked_list_env.c execution/print_list_env.c

SRC_MCHIHAB = main.c \
	$(SRC_CMDS) \
	$(SRC_RED) \
	$(SRC_UTILS_BUILTS)\
	$(SRC_BUILTS)

SRC_SMARSI =  parsing/parsing.c parsing/parsing_file_args.c parsing/quotes_remover.c parsing/signal.c parsing/helpers.c parsing/linked_list/pars_lst.c parsing/linked_list/heredoc_lst.c parsing/syntax/pipe_syntax.c parsing/syntax/syntax.c parsing/syntax/quotes_syntax.c parsing/syntax/files_syntax.c\
	helpers/errors.c\
	lexer/lexer.c lexer/lexer_helper.c lexer/lexer_split.c lexer/lexer_split_helper.c lexer/lexer_strchr.c lexer/lexer_functions.c lexer/lexer_functions2.c\
	memory_handling/memory_handling.c memory_handling/memory_helpers.c \
	expand/expand.c expand/expand_helper.c libft_ftmalloc/free_libft.c libft_ftmalloc/ft_split.c\
	print.c

OBJ_MCHIHAB = $(SRC_MCHIHAB:.c=.o)

OBJ_SMARSI = $(SRC_SMARSI:.c=.o)

all : $(NAME)

$(NAME) : $(OBJ_SMARSI) $(OBJ_MCHIHAB)
	@make -C $(LIBFT_PATH)
	cc $(CFLAGS) $(OBJ_SMARSI) $(OBJ_MCHIHAB) $(NAME_LIBFT) -lreadline -o  $(NAME)

clean :
	@make clean -C $(LIBFT_PATH)
	rm -f $(OBJ_SMARSI) $(OBJ_MCHIHAB)

re : fclean all

fclean : clean
	@make fclean -C $(LIBFT_PATH)
	rm -f $(NAME)

.SECONDARY : $(OBJ_SMARSI) $(OBJ_MCHIHAB)

run : re clean
	./minishell
