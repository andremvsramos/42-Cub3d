# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: andvieir <andvieir@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/14 09:23:06 by andvieir          #+#    #+#              #
#    Updated: 2023/08/14 16:17:43 by andvieir         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d
LIBFT = libft.a
MLX = libmlx.a

#----------DIRS----------#

SRCDIR = ./src/
LIBFTDIR = ./libft/
HEADERDIR = ./headers/
MLXDIR = ./mlx/

SRC =	src/main.c \
		src/map_parser.c \
		src/map_parser_utils.c \
		src/info_parser.c \
		src/file_utils.c \
		src/utils.c \

#----------COMMANDS----------#

CC = cc
CFLAGS = -Wall -Werror -Wextra -g
AR = ar rcs
RM = rm -rf
MLXFLAGS = -L -lmlx -lXext -lX11
MATH = -lm

OBJ = ${SRC:.c=.o}

#----------COLORS----------#
GREEN = \033[0;32m
YELLOW = \033[0;33m
CYAN = \033[1;36m
RED = \033[0;31m

#--------ART & TEXT--------#
MS = " [ Compiled Cub3d ] "
LFT = " [ Compiled Libft ] "
MINILBX = " [ Compiled MiniLibX ]"

#----------RULES----------#
.c.o:
#@$(CC) $(CFLAGS) -c -I$(HEADERDIR) $< -o ${<:.c=.o}
			@mkdir -p bin/$(dir $<)
			@$(CC) $(CFLAGS) -c -I$(HEADERDIR) $< -o bin/$*.o

all:		$(NAME)
			@echo "$(GREEN)$(MS)"
			@echo "$(CYAN) [ Generated: $(NAME) ] "

$(LIBFT):
			@cd $(LIBFTDIR) && $(MAKE) -s
			@echo "$(YELLOW)$(LFT)"

$(MLX):
			@cd $(MLXDIR) && chmod 777 configure && ./configure && $(MAKE)
			@echo "$(RED)$(MINILBX)"

$(NAME):	$(OBJ) $(LIBFT) $(MLX)
			@$(CC) $(CFLAGS) $(OBJ:%=bin/%) $(LIBFTDIR)$(LIBFT) $(MLXDIR)$(MLX) $(MLXFLAGS) $(MATH) -o $(NAME)

clean:
			@$(RM) $(OBJ:%=bin/%)
			@rm -r bin/src
			@cd $(LIBFTDIR) && $(MAKE) -s clean

fclean:		clean
			@$(RM) $(NAME) $(LIBFT) $(MLX)
			@cd $(LIBFTDIR) && $(MAKE) -s fclean
			@cd $(MLXDIR) && $(MAKE) -s fclean

aclean:		all clean

re:			fclean all
