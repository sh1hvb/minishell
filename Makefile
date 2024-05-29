# CC = cc 


CFLAGS = -Wall -Wextra -Werror #-fsanitize=address

NAME = minishell

NAME_LIBFT = libft/libft.a

LIBFT_PATH = libft/

SRC_MCHIHAB = main.c \
	execution/myenv.c execution/ft_export.c execution/utils_env.c \
	execution/builtins_checker.c execution/ft_pwd.c execution/ft_unset.c execution/ft_echo.c \
	execution/builtins_split.c

SRC_SMARSI =  parsing/syntax.c parsing/parsing.c  parsing/linked_list/pars_lst.c parsing/linked_list/heredoc_lst.c \
	helpers/errors.c\
	lexer/lexer.c lexer/lexer_helper.c lexer/lexer_split.c lexer/lexer_strchr.c lexer/lexer_functions.c \
	memory_handling/memory_handling.c memory_handling/memory_helpers.c \
	expand/expand.c libft_ftmalloc/free_libft.c libft_ftmalloc/ft_split.c ft_print.c


OBJ_MCHIHAB = $(SRC_MCHIHAB:.c=.o)

OBJ_SMARSI = $(SRC_SMARSI:.c=.o)

all : $(NAME)

$(NAME) : $(OBJ_SMARSI) $(OBJ_MCHIHAB)
	 make -C $(LIBFT_PATH)
	cc -lreadline -fsanitize=address $(OBJ_SMARSI) $(OBJ_MCHIHAB) $(NAME_LIBFT) -o $(NAME)

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