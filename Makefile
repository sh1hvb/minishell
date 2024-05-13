# CC = cc 

# CFLAGS = -Wall -Wextra -Werror 

NAME = minishell

SRC = main.c

OBJ = $(SRC:.c=.o)

$(NAME) : $(OBJ)
	cc -lreadline main.c

clean :
	rm -f $(OBJ)

fclean : clean
	rm -f $(NAME)