# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: andvieir <andvieir@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/14 09:23:06 by andvieir          #+#    #+#              #
#    Updated: 2023/09/05 15:08:06 by andvieir         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D
LIBFT = libft.a
MLX = libmlx.a

#----------DIRS----------#

SRCDIR = ./src/
LIBFTDIR = ./libft/
HEADERDIR = ./headers/
MLXDIR = ./mlx/

SRC =	src/main.c \
		src/cub3d.c \
		src/utils.c \
		src/map_files/map_init.c \
		src/map_files/map_parser.c \
		src/map_files/map_matrix.c \
		src/map_files/map_parser_utils.c \
		src/map_files/map_closed.c \
		src/map_files/info_parser.c \
		src/map_files/file_utils.c \
		src/graphics/mlx_graphics.c \
		src/graphics/mlx_textures.c \
		src/graphics/mlx_draw.c \
		src/hooks/mlx_hook_events.c \
		src/camera/camera_setup.c \
		src/player/player_setup.c \
		src/raycasting/rays.c \

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
			@$(RM) .map

fclean:		clean
			@$(RM) $(NAME) $(LIBFT) $(MLX)
			@cd $(LIBFTDIR) && $(MAKE) -s fclean
			@cd $(MLXDIR) && $(MAKE) -s clean
			@$(RM) .map

aclean:		all clean

re:			fclean all
