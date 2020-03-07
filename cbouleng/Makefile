# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cbouleng <cbouleng@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/03/05 14:55:52 by cbouleng          #+#    #+#              #
#    Updated: 2020/03/06 10:05:51 by cbouleng         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = gcc

CFLAGS = -Wall -Wextra -Werror -o $(NAME)

SRC = 	get_next_line.c \
		get_next_line_utils.c \
		ft_split.c \
		main.c

OBJ = $(SRC:.c=.o)

$(NAME): $(OBJ)
	@ $(CC) $(CFLAGS) $(OBJ)

all: $(NAME)

clean:
	@rm -f $(OBJ) $(NAME)

fclean: clean
	@rm -f $(NAME)

re : fclean all

.PHONY: clean fclean all re
