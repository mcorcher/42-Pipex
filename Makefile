# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mcorcher <mcorcher@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/12 11:12:31 by mcorcher          #+#    #+#              #
#    Updated: 2025/05/18 19:01:09 by mcorcher         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# -------------------- VARIABLES --------------------

NAME = pipex
CC = cc
RM = rm -f
MAKE = make

CCFLAGS = -Wall -Wextra -Werror -g3

SRC = main.c \
	cmd_parse.c \
	path_utils.c \
	execute.c \
	execute_utils.c\
	cmd_utils.c\

OBJ = $(SRC:.c=.o)

# -------------------- LIBFT & FT_PRINTF --------------------

LIBFT_DIR = ~/Desktop/Cursus/libft
PRINTF_DIR = ~/Desktop/Cursus/ft_printf
LIBFTA = $(LIBFT_DIR)/libft.a
PRINTFA = $(PRINTF_DIR)/libftprintf.a

INCLUDES = -I$(LIBFT_DIR) -I$(PRINTF_DIR)

# -------------------- RULES --------------------

all: $(NAME)

$(NAME): $(OBJ)
	@$(MAKE) -C $(LIBFT_DIR)
	@$(MAKE) -C $(PRINTF_DIR)
	@$(CC) $(CCFLAGS) $(OBJ) $(LIBFTA) $(PRINTFA) -o $(NAME)

%.o: %.c
	@$(CC) $(CCFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@$(RM) $(OBJ)
	@$(MAKE) -C $(LIBFT_DIR) clean
	@$(MAKE) -C $(PRINTF_DIR) clean

fclean: clean
	@$(RM) $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@$(MAKE) -C $(PRINTF_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
