# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ajeannot <ajeannot@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/03/04 13:29:11 by ajeannot          #+#    #+#              #
#    Updated: 2020/06/11 18:21:29 by cbouleng         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRCS = 	annexes/display_string.c \
		annexes/ft_split.c \
		exec/exec_builtins.c \
		exec/exec_cd_main.c \
		exec/exec_cd_path.c \
		exec/exec_echo.c \
		exec/exec_env.c \
		exec/exec_export_backslash.c \
		exec/exec_export_display.c \
		exec/exec_export_error.c \
		exec/exec_export_main.c \
		exec/exec_program.c \
		exec/exec_pwd.c \
		exec/exec_unset_error.c \
		exec/exec_unset_main.c \
		managers/manage_array.c \
		managers/manage_array_extend.c \
		managers/manage_env.c \
		managers/manage_error.c \
		managers/manage_exit_status.c \
		managers/manage_exit.c \
		managers/manage_int_array.c \
		managers/manage_int.c \
		managers/manage_pipe.c \
		managers/manage_redirection.c \
		managers/manage_str_array.c \
		managers/manage_str_dup.c \
		managers/manage_str.c \
		body/minishell_setup.c \
		body/minishell_setup_env.c \
		body/minishell_setup_shlvl.c \
		body/minishell_quit.c \
		body/minishell_exec.c \
		body/minishell.c \
		gnl/get_next_line.c \
		gnl/get_next_line_utils.c \
		parsing/check.c \
		parsing/check_rd.c \
		parsing/get_dollar.c \
		parsing/get_dollar_2.c \
		parsing/get_rdo.c \
		parsing/get_redir.c \
		parsing/get_redir_2.c \
		parsing/list_it.c \
		parsing/list_utils.c \
		parsing/list_utils_2.c \
		parsing/parsing.c \
		parsing/map_quote.c \
		parsing/split_plus.c \
		parsing/utils.c \
		parsing/utils_2.c \
		parsing/utils_3.c \
		clear_it/clear_before_exec.c \
		clear_it/clear_before_exec_2.c \
		clear_it/clear_echo_bad_env.c \
		clear_it/clear_stock_rd.c \

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