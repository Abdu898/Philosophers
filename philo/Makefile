
NAME = philo

SRC = handle_args.c init_forks.c philo.c \
		routine.c time.c utils.c dpug.c death_checker.c

CC = cc

CFLAGS = -Wall -Werror -Wextra -g -fsanitize=thread

INCLUDE = -lpthread 

COMPILE = $(CC) $(CFLAGS) $(INCLUDE)

all: $(NAME)

$(NAME): $(SRC)
	@$(CC) $(SRC) -o $(NAME)

clean:
	@rm -f $(NAME)


fclean:	clean

re: fclean all

.PHONY: all clean fclean re
