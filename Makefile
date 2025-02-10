NAME = philo
CC = cc 
FLAGS = -Wall -Wextra -Werror
RM = rm -f
SRC = main.c \
		philo.h

OBJ = $(SRC:.c=.o)

all: $(NAME)
$NAME: $(OBJ)
	$(CC) $(FLAGS) -o $(NAME) $(OBJ)
	${MAKE} clean

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re