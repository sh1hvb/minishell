# CC = cc 

CFLAGS = -Wall -Wextra -Werror #-fsanitize=address

NAME = minishell

NAME_LIBFT = libft/libft.a

LIBFT_PATH = libft/

SRC = main.c \
	parsing/syntax.c parsing/parsing.c  parsing/linked_list/pars_lst.c parsing/linked_list/heredoc_lst.c\
	helpers/errors.c lexer/lexer.c lexer/lexer_helper.c \
	lexer/lexer_split.c lexer/lexer_strchr.c lexer/lexer_functions.c memory_handling/memory_handling.c\
	memory_handling/memory_helpers.c execution/myenv.c \
	expand/expand.c libft_ftmalloc/free_libft.c libft_ftmalloc/ft_split.c ft_print.c

OBJ = $(SRC:.c=.o)

all : $(NAME)

$(NAME) : $(OBJ)
	 make -C $(LIBFT_PATH)
	cc -lreadline $? $(NAME_LIBFT) -o $@

clean :
#	make clean -C $(LIBFT_PATH)
	rm -f $(OBJ)

re : fclean all

fclean : clean
	make fclean -C $(LIBFT_PATH)
	rm -f $(NAME)

.SECONDARY : $(OBJ)

run : re clean
	./minishell