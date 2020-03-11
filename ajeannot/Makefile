# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ajeannot <ajeannot@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/03/04 13:29:11 by ajeannot          #+#    #+#              #
#    Updated: 2020/03/09 13:34:16 by ajeannot         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRCS = 	annexes/display_string.c \
		annexes/ft_split.c \
		exec/exec_cd.c \
		exec/exec_export.c \
		exec/exec_builtins.c \
		exec/exec_unset.c \
		exec/exec_program.c \
		managers/manage_array.c \
		managers/manage_env.c \
		managers/manage_string.c \
		minishell.c \
		gnl/get_next_line.c \
		gnl/get_next_line_utils.c \

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

prog:		test.c
			$(CC) $(FLAGS) -o prog test.c

test : 		re
			echo
			echo
			./$(NAME)


.PHONY: 		clean fclean all re
.SILENT:
