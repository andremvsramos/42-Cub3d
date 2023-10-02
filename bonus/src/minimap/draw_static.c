/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_static.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andvieir <andvieir@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 09:50:43 by tsodre-p          #+#    #+#             */
/*   Updated: 2023/10/02 10:00:33 by andvieir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/cub3d_bonus.h"

/**
 * @brief Draw a static cube on the minimap image.
 *
 * The `draw_static_cube` function draws a square of a specified `type` (color)
 * onto the minimap image at the given coordinates.
 *
 * @param cub Pointer to the Cub3D game configuration structure.
 * @param type The type (color) of the cube to be drawn.
 */
void	draw_static_cube(t_Cub3d *cub, int type)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < 13)
	{
		j = 0;
		while (j < 13)
		{
			my_mlx_pixel_put(cub->minimap->img, (cub->minimap->draw_x + j),
				(cub->minimap->draw_y + i), type);
			j++;
		}
		i++;
	}
}

/**
 * @brief Draw the static player position on the minimap image.
 *
 * The `draw_static_player` function marks the player's position on the minimap
 * image as a red square. It uses the player's coordinates to determine the
 * position to draw.
 *
 * @param cub Pointer to the Cub3D game configuration structure.
 */
void	draw_static_player(t_Cub3d *cub)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < 13)
	{
		j = 0;
		while (j < 13)
		{
			my_mlx_pixel_put(cub->minimap->img, (cub->minimap->player_x + j),
				(cub->minimap->player_y + i), RED);
			j++;
		}
		i++;
	}
}

/**
 * @brief Draw the static map grid on the minimap image.
 *
 * The `draw_static_map` function draws a static representation of the game map
 * on the minimap image. It iterates through the map matrix and draws cubes of
 * different colors based on the map elements (walls, empty space, etc.).
 *
 * @param cub Pointer to the Cub3D game configuration structure.
 */
void	draw_static_map(t_Cub3d *cub)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (y < cub->map->n_lines + 1)
	{
		x = 0;
		while (x < cub->map->max_line_len - 1)
		{
			if (ft_strchr("1", cub->map->matrix[y][x]))
				draw_static_cube(cub, GREY);
			else if (ft_strchr("0NSEW", cub->map->matrix[y][x]))
				draw_static_cube(cub, WHITE);
			x++;
			cub->minimap->draw_x += 13;
		}
		cub->minimap->draw_y += 13;
		cub->minimap->draw_x = 0;
		y++;
	}
}
