# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ajeannot <ajeannot@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/03/04 13:29:11 by ajeannot          #+#    #+#              #
#    Updated: 2020/03/04 16:36:42 by ajeannot         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRCS = 	fct_annexes.c \
		ft_split.c \
		fct_execs.c \
		get_next_line/get_next_line.c \
		get_next_line/get_next_line_utils.c \

OBJS = $(SRCS:.c=.o)
OBJS_DIR = objs/
INCL = -I . -I/get_next_line/
CC = gcc
FLAGS = -Wall -Wextra -Werror

%.o: 		%.c
			echo $(notdir $@) "\033[0;32m ==> created\033[0m"
			$(CC) $(FLAGS) -c $< -o $(OBJS_DIR)$(notdir $@)

all: $(NAME)

$(NAME):	$(OBJS)
			echo Linking "\033[0;35m ==> in progress\033[0m"
			$(CC) $(FLAGS) $(addprefix $(OBJS_DIR),$(notdir $(OBJS))) -o $@
			echo $(NAME) "\033[0;32m ==> done\033[0m"

clean :
			rm -rf $(addprefix $(OBJS_DIR),$(notdir $(OBJS)))
			echo objects files "\033[0;31m ==> deleted\033[0m"

fclean : 	clean
			rm -rf $(NAME)
			echo $(NAME) "\033[0;31m ==> deleted\033[0m"

re:			fclean all

test : 		re
			echo
			echo
			./$(NAME)


.PHONY: 		clean fclean all re
.SILENT:
