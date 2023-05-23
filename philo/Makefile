
NAME = philo

SRC = init_args.c init_forks.c philo.c \
		routine.c time.c utils.c death_checker.c

CC = cc

CFLAGS = -Wall -Werror -Wextra

INCLUDE = -lpthread

DEPUG = -g -fsanitize=thread 

MAKEFILE = Makefile

HEADER = philo.h

COMPILE = $(CC) $(CFLAGS) $(INCLUDE)

OBJ = $(SRC:.c=.o)

$(NAME): $(SRC) $(MAKEFILE) $(HEADER)
	@$(COMPILE) $(SRC) -o $(NAME)

all : $(NAME)

depug:
	@$(COMPILE) $(DEPUG) $(SRC) -o $(NAME)

clean:
	@rm -f $(OBJ)


fclean:	clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
