/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_dynamic.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 14:32:51 by tsodre-p          #+#    #+#             */
/*   Updated: 2023/09/27 23:38:42 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/cub3d.h"

/**
 * @brief Draw a dynamic cube on the minimap image.
 *
 * The `draw_dynamic_cube` function draws a square of a specified `type` (color)
 * onto the minimap image at the current drawing position. It is used to
 * represent dynamic objects on the minimap.
 *
 * @param cub Pointer to the Cub3D game configuration structure.
 * @param type The type (color) of the cube to be drawn.
 */
void	draw_dynamic_cube(t_Cub3d *cub, int type)
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
 * @brief Draw the dynamic map on the minimap image.
 *
 * The `draw_dynamic_map` function draws a dynamic portion of the game map onto
 * the minimap image. It considers the player's position and draws a portion of
 * the map around the player, up to 11x11 tiles, with different colors based on
 * the map elements (walls, empty space, etc.). This function is used to provide
 * a dynamic representation of the game world on the minimap.
 *
 * @param cub Pointer to the Cub3D game configuration structure.
 * @param temp_x Temporary variable for the horizontal position calculation.
 * @param temp_y Temporary variable for the vertical position calculation.
 */
void	draw_dynamic_map(t_Cub3d *cub, int temp_x, int temp_y)
{
	int	x;
	int	y;

	y = (int)cub->player->pos_y - 5;
	temp_y = y;
	while (y < (temp_y + 11))
	{
		x = (int)cub->player->pos_x - 5;
		temp_x = x;
		while (x < (temp_x + 11))
		{
			if (y >= cub->map->n_lines + 1 || y < 0
				|| x >= max_x_array(cub) || x < 0)
				draw_dynamic_cube(cub, BLACK);
			else if (ft_strchr("19 ", cub->map->matrix[y][x]))
				draw_dynamic_cube(cub, GREY);
			else if (ft_strchr("0NSWE", cub->map->matrix[y][x]))
				draw_dynamic_cube(cub, WHITE);
			x++;
			cub->minimap->draw_x += 13;
		}
		cub->minimap->draw_y += 13;
		cub->minimap->draw_x = 0;
		y++;
	}
}

/**
 * @brief Draw the dynamic player position on the minimap image.
 *
 * The `draw_dynamic_player` function marks the player's position on the minimap
 * image as a red square. It uses a fixed position relative to the minimap area
 * to draw the player's representation. This function provides a dynamic
 * indicator of the player's location on the minimap.
 *
 * @param cub Pointer to the Cub3D game configuration structure.
 */
void	draw_dynamic_player(t_Cub3d *cub)
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
			my_mlx_pixel_put(cub->minimap->img, ((13 * 5) + j),
				((13 * 5) + i), RED);
			j++;
		}
		i++;
	}
}
