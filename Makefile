# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: junhpark <junhpark@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/02/01 20:54:55 by junhpark          #+#    #+#              #
#    Updated: 2021/02/02 13:46:10 by kyeo             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= minishell

CC				= gcc

SRC_NAME		= cd.c \
				echo.c \
				env.c \
				exec.c \
				exit.c \
				export.c \
				free.c \
				get_cmd.c \
				handle_error.c \
				init_env.c \
				main.c \
				parse_cmd.c \
				parse_redirection.c \
				parse_utils.c \
				path.c \
				pipe_utils.c \
				prepare_line.c \
				prompt.c \
				pwd.c \
				redirection_utils.c \
				redirection.c \
				refine_cmd.c \
				set_cmd_data.c \
				start_end.c \
				unset.c \
				path_utils.c \
				signal.c

SRC_PATH = ./src

SRC = $(addprefix $(SRC_PATH)/, $(SRC_NAME))

OBJ_NAME = $(SRC_NAME:.c=.o)

OBJ_PATH = ./obj

OBJ = $(addprefix $(OBJ_PATH)/, $(OBJ_NAME))

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	@mkdir $(OBJ_PATH) 2> /dev/null || true
	@gcc $(CFLAG) $(HEADER) -o $@ -c $<

HEADER	= -I./include

CFLAG	= -Wall -Wextra -Werror

LIBFT	= ./lib/libft.a

LIBS	= -L./lib/libft -lft

RM	= rm -rf

all	: $(NAME)

$(NAME)	: $(OBJ) $(LIBFT)
	gcc -o $(NAME) $(OBJ) $(HEADER) $(CFLAG) $(LIBS)

$(LIBFT):
	$(MAKE) -C ./lib/libft

clean	:
	$(MAKE) -C ./lib/libft clean
	rm -rf $(OBJ_PATH)

fclean	: clean
	$(MAKE) -C ./lib/libft fclean
	rm -rf $(NAME)

re		: fclean all

.PHONY: all clean fclean re
