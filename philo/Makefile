NAME = philo

CC = cc -g
CFLAGS = -Wall -Wextra -Werror -fsanitize=thread -g3


SRCS =  main.c utils.c utils_philos.c philo.c  philo_2.c philo_3.c philo_4.c    


OBJS = $(SRCS:%.c=$(OBJ_DIR)/%.o)
OBJ_DIR = .obj

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) | $(OBJ_DIR)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) 

$(OBJ_DIR):
	mkdir .obj

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	$(CC) $(CFLAGS)  -c $< -o $@

clean:
	rm -rf .obj

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

.SECONDARY: ${OBJS}
