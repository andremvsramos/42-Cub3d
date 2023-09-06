/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 22:21:18 by marvin            #+#    #+#             */
/*   Updated: 2023/08/29 22:21:18 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/cub3d.h"

/**
 * Load image textures for walls and floors.
 *
 * This function loads image textures for walls and floors from external files
 * and stores them in the `cub` structure. It uses the mlx_xpm_file_to_image
 * function from a graphics library (presumably mlx) to load the images.
 *
 * @param cub A pointer to the Cub3d structure.
 */
static void	get_images(t_Cub3d *cub)
{
	int		img_width;
	int		img_height;
	int		*width;
	int		*height;

	img_width = 8;
	img_height = 8;
	width = &img_width;
	height = &img_height;
	cub->img_wall = mlx_xpm_file_to_image(
			cub->mlx_ptr, WALL_IMG, width, height);
	cub->img_floor = mlx_xpm_file_to_image(
			cub->mlx_ptr, FLOOR_IMG, width, height);
}

/**
 * Display an image based on a miscellaneous character.
 *
 * This function displays an image on the window based on the value of the
 * 'miscellaneous' character. If 'miscellaneous' is '1', it displays the wall
 * image; otherwise, it displays the floor image. It uses the mlx_put_image_to_window
 * function from a graphics library (presumably mlx) to display the image.
 *
 * @param cub A pointer to the Cub3d structure.
 * @param miscellaneous A character indicating the type of image to display ('1' for wall, other for floor).
 * @param x The x-coordinate of the image on the window.
 * @param y The y-coordinate of the image on the window.
 */
static void	image_conditions(t_Cub3d *cub, char miscellaneous, int x, int y)
{
	if (miscellaneous == '1')
		mlx_put_image_to_window(
			cub->mlx_ptr, cub->win_ptr, cub->img_wall, x, y);
	else
		mlx_put_image_to_window(
			cub->mlx_ptr, cub->win_ptr, cub->img_floor, x, y);
}

/**
 * Draw a 2D map representation of the game world.
 *
 * This function draws a 2D map representation of the game world using images
 * loaded into the `cub` structure. It iterates through the game's map matrix,
 * where '1' represents walls and '0' represents floor tiles, and uses the
 * image_conditions function to display the appropriate images on the window.
 *
 * @param cub A pointer to the Cub3d structure.
 */
int	draw_2d_map(t_Cub3d *cub)
{
	int	i;
	int	j;

	get_images(cub);
	if (cub->minimap->old_rot != new_rot ||
		cub->minimap->old_player_x != new_player_x ||
		cub->minimap->old_player_y != new_player_y)
	{
		i = 0;
		j = 0;
		while (i < cub->map->n_lines + 1)
		{
			j = 0;
			while (j < cub->map->max_line_len - 1)
			{
				if (cub->map->matrix[i][j] == '1')
					image_conditions(cub, '1', j * 8, i * 8);
				else
					image_conditions(cub, '0', j * 8, i * 8);
				j++;
			}
			i++;
		}
	}
	return (0);
}
