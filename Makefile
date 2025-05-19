# Variables
CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME = pipex
SRCS = main.c cmd_parse.c execute.c path_utils.c execute_utils.c cmd_utils.c
OBJS = $(SRCS:.c=.o)

# Library paths
LIBFT_DIR = ~/Desktop/Cursus/libft
PRINTF_DIR = ~/Desktop/Cursus/ft_printf
LIBFTA = $(LIBFT_DIR)/libft.a
PRINTFA = $(PRINTF_DIR)/libftprintf.a

INCLUDES = -I$(LIBFT_DIR) -I$(PRINTF_DIR)

# Rules
all: $(LIBFTA) $(PRINTFA) $(NAME)

$(LIBFTA):
	@make -C $(LIBFT_DIR)

$(PRINTFA):
	@make -C $(PRINTF_DIR)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LIBFTA) $(PRINTFA)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJS)
	make -C $(LIBFT_DIR) clean
	make -C $(PRINTF_DIR) clean

fclean: clean
	rm -f $(NAME)
	make -C $(LIBFT_DIR) fclean
	make -C $(PRINTF_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
