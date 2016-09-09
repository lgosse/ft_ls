# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lgosse <lgosse@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/03/07 16:47:05 by lgosse            #+#    #+#              #
#    Updated: 2016/06/07 16:50:31 by lgosse           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_NAME =	ft_ls.c \
			treat_args.c \
			treat_dir.c \
			sort.c \
			read.c \
			longfmt.c \
			getmode.c \
			sortfuncs.c \
			freedir.c \
			error.c

OBJ_NAME = $(SRC_NAME:.c=.o)

NAME = ft_ls

SRC_PATH = src/
LIB_PATH = libft/includes/
OBJ_PATH = obj/

SRC_LIB = $(addprefix $(SRC_PATH),$(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH),$(OBJ_NAME))
LIB = $(addprefix -I,$(LIB_PATH))

CC = gcc
CFLAGS = -Iincludes -Wall -Wextra -Werror
LDFLAGS = -Llibft -lft
LDLIBS = -lft

all:$(NAME)

$(NAME):$(OBJ)
	@make -C libft/ -j 8 > /dev/null
	@$(CC) $(LDFLAGS) $(LDLIBS) $^ -o $@
	@echo "\033[32mCompilation done !\033[0m"

$(OBJ_PATH)%.o:$(SRC_PATH)%.c
	@mkdir -p $(OBJ_PATH)
	@$(CC) $(CFLAGS) $(LIB) -o $@ -c $<

clean:
	@make -C libft/ fclean > /dev/null
	@rm -fv $(OBJ) > /dev/null
	@rm -rfv $(OBJ_PATH) > /dev/null
	@echo "\033[32mObjects cleaned !\033[0m"

fclean: clean
	@rm -fv $(NAME) > /dev/null
	@echo "\033[32mExecutable cleaned !\033[0m"

re: fclean all

.PHONY: all, clean, fclean, re
