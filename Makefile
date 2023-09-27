# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: programming-pc <programming-pc@student.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/14 09:23:06 by andvieir          #+#    #+#              #
#    Updated: 2023/09/27 21:36:56 by programming      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D
NAME_BONUS = cub3D_Bonus
LIBFT = libft.a
MLX = libmlx.a

#----------DIRS----------#

SRCDIR = ./mandatory/src/
HEADERDIR = ./mandatory/headers/
BONUSDIR = ./bonus/src/
BONUSHEADER = ./bonus/headers/
LIBFTDIR = ./mandatory/libft/
BONUSLIBFTDIR = ./bonus/libft/
MLXDIR = ./mlx/

SRC =		mandatory/src/main.c \
			mandatory/src/cleanup.c \
			mandatory/src/cleanup2.c \
			mandatory/src/map_files/map_init.c \
			mandatory/src/map_files/map_parser.c \
			mandatory/src/map_files/map_matrix.c \
			mandatory/src/map_files/map_parser_utils.c \
			mandatory/src/map_files/map_closed.c \
			mandatory/src/map_files/map_colors.c \
			mandatory/src/map_files/info_parser.c \
			mandatory/src/map_files/file_utils.c \
			mandatory/src/graphics/mlx_graphics.c \
			mandatory/src/graphics/mlx_textures.c \
			mandatory/src/graphics/mlx_textures_utils.c \
			mandatory/src/graphics/restore_doors.c \
			mandatory/src/graphics/main_menu.c \
			mandatory/src/hooks/mlx_hook_events.c \
			mandatory/src/hooks/mouse_events.c \
			mandatory/src/camera/camera_setup.c \
			mandatory/src/player/player_setup.c \
			mandatory/src/player/player_movement.c \
			mandatory/src/player/player_action.c \
			mandatory/src/player/player_gun.c \
			mandatory/src/raycasting/rays.c \
			mandatory/src/raycasting/rays_utils.c \
			mandatory/src/minimap/minimap.c \
			mandatory/src/minimap/draw_static.c \
			mandatory/src/minimap/draw_dynamic.c \
			mandatory/src/minimap/minimap_utils.c \

BONSRC =	bonus/src/main.c \
			bonus/src/cleanup.c \
			bonus/src/cleanup2.c \
			bonus/src/map_files/map_init.c \
			bonus/src/map_files/map_parser.c \
			bonus/src/map_files/map_matrix.c \
			bonus/src/map_files/map_parser_utils.c \
			bonus/src/map_files/map_closed.c \
			bonus/src/map_files/map_colors.c \
			bonus/src/map_files/info_parser.c \
			bonus/src/map_files/file_utils.c \
			bonus/src/graphics/mlx_graphics.c \
			bonus/src/graphics/mlx_textures.c \
			bonus/src/graphics/mlx_textures_utils.c \
			bonus/src/graphics/restore_doors.c \
			bonus/src/graphics/main_menu.c \
			bonus/src/hooks/mlx_hook_events.c \
			bonus/src/hooks/mouse_events.c \
			bonus/src/camera/camera_setup.c \
			bonus/src/player/player_setup.c \
			bonus/src/player/player_movement.c \
			bonus/src/player/player_action.c \
			bonus/src/player/player_gun.c \
			bonus/src/raycasting/rays.c \
			bonus/src/raycasting/rays_utils.c \
			bonus/src/minimap/minimap.c \
			bonus/src/minimap/draw_static.c \
			bonus/src/minimap/draw_dynamic.c \
			bonus/src/minimap/minimap_utils.c \

#----------COMMANDS----------#

CC = cc
CFLAGS = -Wall -Werror -Wextra -g

RM = rm -rf
MLXFLAGS = -L -lmlx -lXext -lX11
MATH = -lm

OBJ = ${SRC:.c=.o}
BONOBJ = ${BONSRC:.c=.o}

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

bonus:		$(NAME_BONUS)
			@echo "$(GREEN)$(MS)"
			@echo "$(CYAN) [ Generated: $(NAME_BONUS) ] "

$(LIBFT):
			@cd $(LIBFTDIR) && $(MAKE) -s
			@echo "$(YELLOW)$(LFT)"

$(MLX):
			@cd $(MLXDIR) && $(MAKE)
			@echo "$(RED)$(MINILBX)"

$(NAME):	$(OBJ) $(LIBFT) $(MLX)
			@$(CC) $(CFLAGS) $(OBJ:%=bin/%) $(LIBFTDIR)$(LIBFT) $(MLXDIR)$(MLX) $(MLXFLAGS) $(MATH) -o $(NAME)

$(NAME_BONUS):	$(BONOBJ) $(LIBFT) $(MLX)
				@$(CC) $(CFLAGS) $(BONOBJ:%=bin/%) $(BONUSLIBFTDIR)$(LIBFT) $(MLXDIR)$(MLX) $(MLXFLAGS) $(MATH) -o $(NAME_BONUS)

mlxconfig:
			@cd $(MLXDIR) && chmod 777 configure && ./configure

clean:
			@$(RM) $(OBJ:%=bin/%) $(BONOBJ:%=bin/%)
			@rm -r bin/mandatory/src
			@cd $(LIBFTDIR) && $(MAKE) -s clean
			@$(RM) .map

fclean:		clean
			@$(RM) $(NAME) $(NAME_BONUS) $(LIBFT) $(MLX)
			@cd $(LIBFTDIR) && $(MAKE) -s fclean
			@cd $(MLXDIR) && $(MAKE) -s clean
			@$(RM) .map

aclean:		all clean

re:			fclean all
