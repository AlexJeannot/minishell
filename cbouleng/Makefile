# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cbouleng <cbouleng@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/03/05 14:55:52 by cbouleng          #+#    #+#              #
#    Updated: 2020/03/11 16:06:54 by cbouleng         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = gcc

CFLAGS = -Wall -Wextra -Werror -o $(NAME)

SRC = 	get_next_line.c \
		get_next_line_utils.c \
		map_quote.c \
		split_plus.c \
		list_it.c \
		list_utils.c \
		get_dollar.c \
		get_dollar_utils.c \
		get_dollar_utils_2.c \
		clean_before_print.c \
		utils.c \
		main.c

OBJ = $(SRC:.c=.o)

$(NAME): $(OBJ)
	@ $(CC) $(CFLAGS) $(OBJ)

all: $(NAME)

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re : fclean all

test : $(NAME)
	./$(NAME)

.PHONY: clean fclean all re test
