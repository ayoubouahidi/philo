NAME = philo

CC = cc -g
CFLAGS = -Wall -Wextra -Werror -fsanitize=thread -g3


SRCS =  main.c utils.c utils_philos.c philo.c  philo_2.c philo_3.c philo_4.c    


OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) 

%.o: %.c
	$(CC) $(CFLAGS)  -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

.SECONDARY: ${OBJS}
