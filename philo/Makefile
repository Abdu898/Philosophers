
NAME = philo

SRC = handle_args.c philo.c routine.c time.c utils.c dpug.c

CC = cc

CFLAGS = -Wall -Werror -Wextra -g

INCLUDE = -lpthread

COMPILE = $(CC) $(CFLAGS) $(INCLUDE)

all: $(NAME)

# %.o: %.c
# 	$(CC) $(CFLAGS) -c $< -o $@

$(NAME):
	@$(CC) $(SRC) -o $(NAME)

clean:
	@rm -f $(NAME)


fclean:	clean

re: fclean all

.PHONY: all clean fclean re
