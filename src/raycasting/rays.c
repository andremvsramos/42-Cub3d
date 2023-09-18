/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andvieir <andvieir@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 14:45:15 by andvieir          #+#    #+#             */
/*   Updated: 2023/09/18 18:30:25 by andvieir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/cub3d.h"

/**
 * @brief Get the color of a pixel at a specified position in an image.
 *
 * The `my_mlx_pixel_get` function retrieves the color of a pixel located at the
 * specified `(x, y)` position within an image represented by the `img`
 * structure. It calculates the memory offset based on the image's address,
 * length, and bits per pixel, and returns the color as an unsigned integer.
 *
 * @param img Pointer to the `t_ImageControl` structure representing the image.
 * @param x The horizontal position (column) of the pixel.
 * @param y The vertical position (row) of the pixel.
 * @return The color of the pixel at `(x, y)` as an unsigned integer.
 */
int	my_mlx_pixel_get(t_ImageControl *img, int x, int y)
{
	return (*(unsigned int *)((img->addr + (y * img->len) + \
	(x * img->bpp / 8))));
}

/**
 * @brief Initialize ray properties for a specific column of the screen.
 *
 * The `init_rays` function initializes the properties of a ray for a specific
 * column of the screen during the raycasting process. It calculates the
 * camera's position on the screen (`camera_x`), the ray's direction (`raydir_x`
 * and `raydir_y`), and the initial map position (`map_x` and `map_y`).
 * Additionally, it calculates the delta distance (`ddist_x` and `ddist_y`)
 * required to move from one grid cell to the next in both the horizontal and
 * vertical directions.
 *
 * @param cub Pointer to the `t_Cub3d` structure containing program context and
 * data.
 * @param cam Pointer to the `t_CameraConfig` structure containing camera
 * configuration data.
 * @param x The current screen column being processed.
 */
void	init_rays(t_Cub3d *cub, t_CameraConfig *cam, int x)
{
	cam->camera_x = 2 * x / (double)WINDOW_X - 1;
	cam->raydir_x = cub->player->dir_x + cam->plane_x * cam->camera_x;
	cam->raydir_y = cub->player->dir_y + cam->plane_y * cam->camera_x;
	cam->map_x = floor(cub->player->pos_x);
	cam->map_y = floor(cub->player->pos_y);
	if (!cam->raydir_x)
		cam->ddist_x = 1e30;
	else
		cam->ddist_x = fabs(1 / cam->raydir_x);
	if (!cam->raydir_y)
		cam->ddist_y = 1e30;
	else
		cam->ddist_y = fabs(1 / cam->raydir_y);
}

/**
 * @brief Draw the scene by casting rays from the camera for each screen column.
 *
 * The `draw_rays` function is responsible for rendering the 3D scene by casting
 * rays from the camera's perspective for each screen column. It iterates over
 * all columns, initializes ray properties, performs raycasting, calculates wall
 * heights, determines wall directions, and applies textures to render the
 * walls. Additionally, it renders the ceiling and floor before processing each
 * column.
 *
 * @param cub Pointer to the `t_Cub3d` structure containing program context and
 * data.
 */
void	draw_rays(t_Cub3d *cub)
{
	int				x;/*
	int				y; */
	t_CameraConfig	*cam;

	cam = cub->cam;
	x = 0;
	cam_utils_init(cam);
	render_ceilling_floor(cub);
	while (x < WINDOW_X)
	{
		init_rays(cub, cam, x);
		step_calculation(cam, cub->player);
		apply_dda(cam, cub->map);
		calculate_wall_height(cam);
		get_wall_direction(cub->cam);
		apply_texture(cub, cub->cam, x, cam->wall_dir);
		x++;
	}
}
