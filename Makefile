# CC = cc 

CFLAGS = -Wall -Wextra -Werror #-fsanitize=address

NAME = minishell

NAME_LIBFT = libft/libft.a

LIBFT_PATH = libft/

SRC = main.c parcing/syntax.c  helpers/errors.c lexer/lexer.c lexer/lexer_helper.c \
	lexer/lexer_split.c lexer/lexer_strchr.c lexer/lexer_functions.c memory_handling/memory_handling.c\
	memory_handling/memory_helpers.c execution/myenv.c execution/ft_export.c execution/utils_env.c \
	execution/builtins_checker.c execution/ft_pwd.c execution/ft_unset.c execution/ft_echo.c

OBJ = $(SRC:.c=.o)

$(NAME) : $(OBJ)
	 make -C $(LIBFT_PATH)
	cc -lreadline $(OBJ) $(NAME_LIBFT) -o $(NAME)

clean :
	make clean -C $(LIBFT_PATH)
	rm -f $(OBJ)

fclean : clean
	make fclean -C $(LIBFT_PATH)
	rm -f $(NAME)